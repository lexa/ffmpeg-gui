#include "FFMPEG.hpp"


LibAVC* LibAVC::uniqueInstance = NULL;

LibAVC* 
LibAVC::instance()
{
	if (!uniqueInstance)
		uniqueInstance = new LibAVC;
	return uniqueInstance;
}

LibAVC::LibAVC()
{
	av_register_all();
}
LibAVC::~LibAVC()
{
//	av_exit(0);//FIXME это точно нормально?
}


QStringList
FileFormats(bool need_decode, bool need_encode)
{
	AVInputFormat *ifmt=NULL;
	AVOutputFormat *ofmt=NULL;
	const char *last_name;
	
	QStringList availFileFormats;
	LibAVC::instance();//убедились что всё наместе
	
	last_name= "000";
	for(;;){
		int decode=0;
		int encode=0;
		const char *name=NULL;
		const char *long_name=NULL;

		while((ofmt= av_oformat_next(ofmt))) {
			if((name == NULL || strcmp(ofmt->name, name)<0) &&
			   strcmp(ofmt->name, last_name)>0){
				name= ofmt->name;
				long_name= ofmt->long_name;
				encode=1;
			}
		}
		while((ifmt= av_iformat_next(ifmt))) {
			if((name == NULL || strcmp(ifmt->name, name)<0) &&
			   strcmp(ifmt->name, last_name)>0){
				name= ifmt->name;
				long_name= ifmt->long_name;
				encode=0;
			}
			if(name && strcmp(ifmt->name, name)==0)
				decode = 1;
		}
		if(name==NULL)
			break;
		last_name= name;

		if (need_decode && decode)
			availFileFormats.append(QString(name));
		if (need_encode && encode)
			availFileFormats.append(name);
	}
	return availFileFormats;
}

Codecs::Codecs(QObject* parent):
	QObject(parent)
{
    AVCodec *p=NULL, *p2;
    const char *last_name;

    LibAVC::instance();//убедились что всё наместе
    last_name= "000";
    for(;;){
        int decode=0;
        int encode=0;
        int cap=0;

        p2=NULL;
        while((p= av_codec_next(p))) {
            if((p2==NULL || strcmp(p->name, p2->name)<0) &&
                strcmp(p->name, last_name)>0){
                p2= p;
                decode= encode= cap=0;
            }
            if(p2 && strcmp(p->name, p2->name)==0){
                if(p->decode) decode=1;
                if(p->encode) encode=1;
                cap |= p->capabilities;
            }
        }
        if(p2==NULL)
            break;
        last_name= p2->name;

	CodecT tmp;
	tmp.name = p2->name;
	tmp.type = p2->type;
	tmp.coder = (decode ? DECODE : 0) | (encode ? ENCODE : 0);

	allCodecs.append(tmp);
	
    }
}

QStringList 
Codecs::getAvailableCodecs(CodecType type, int coder) const
{
	QList <CodecT>::iterator c(allCodecs.begin());
	QStringList rez;

	for(; c != allCodecs.end(); c++) 
	{
		if ((c->type == type) && (0 != (coder & c->coder)))
		{
			rez.append (c->name);
		}
	}
	return rez;
}

QStringList
getAvailableDecodeFileFormats()
{
	return FileFormats(0, 1);
}

QStringList
getAvailableEncodeFileFormats()
{
	return FileFormats(1, 0);
}

QString
FileInfo::container() const
{
	return container_;
}

FileInfo::FileInfo(QUrl filename)
{
	LibAVC::instance();

	AVFormatContext *pFormatCtx;
	int err;
//	QList<QPair<CodecType, QString> > rez;

	if(0 != (err = av_open_input_file(&pFormatCtx, filename.toString().toUtf8().data(), NULL, 0, NULL)))
	{
		qWarning() << "av_open_input_file" << err;
		throw QString("can't open input file");
	}
	// Retrieve stream information
	if(0 > (err = av_find_stream_info(pFormatCtx)))
	{
		qWarning() << "av_find_stream_info" ;
		av_close_input_file(pFormatCtx);
		throw QString("can't find stream info");
	}

	container_ = QString(pFormatCtx->iformat->name);

//	dump_format(pFormatCtx, 0, "нужный файл", 0);//for debugging
	
//	tree->clear();
//	QTreeWidgetItem* container =  new QTreeWidgetItem(QStringList(tr("Container")) << pFormatCtx->iformat->name);
//	tree->addTopLevelItem (container);
	for(unsigned int i=0; i<pFormatCtx->nb_streams; i++) 
	{
//		QString num;
//		num.setNum(i);
//		QStringList fields(QString(tr("Stream ")) + num);
		//("Stream") << pFormatCtx->streams[i]->codec->codec_name;
		// AVCodecContext *pCodecCtx =  pFormatCtx->streams[i]->codec;
		// switch (pCodecCtx->codec_type)
		// {
		// case    CODEC_TYPE_UNKNOWN  : fields << "UNKNOWN"; break ;
		// case    CODEC_TYPE_VIDEO : fields << "VIDEO"; break ;
		// case 	CODEC_TYPE_AUDIO : fields << "AUDIO"; break ;
		// case	CODEC_TYPE_DATA : fields << "DATA"; break ;
		// case	CODEC_TYPE_SUBTITLE : fields << "SUBTITLE"; break ;
		// case	CODEC_TYPE_NB : fields << "NB"; break ;
		// default: 
		// 	fields << "undefined type"; break ;
		// }
//		AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
//		if(pCodec == NULL) {
//			qWarning() << "Unsupported codec!";
			//TODO отмечать в графике это
//		}
		
		
		char buf[256];
		avcodec_string(buf, sizeof(buf), pFormatCtx->streams[i]->codec, false);//шоцетаке ?
//		qWarning(buf);
//		fields << buf;

		char *crop_buf = buf;
		while (! isblank(*crop_buf++));//отсекаем первое слово в строке
		streams.append(qMakePair(pFormatCtx->streams[i]->codec->codec_type, QString(crop_buf)));

	}	   
	av_close_input_file(pFormatCtx);
}


QList<QPair<CodecType, QString> > 
FileInfo::getStreams()
{
	return streams;
}
