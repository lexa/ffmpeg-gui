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



FileFormats::FileFormats(QObject *parent)
	:QObject(parent)
{
	AVInputFormat *ifmt=NULL;
	AVOutputFormat *ofmt=NULL;
	const char *last_name;
	
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

		if (decode)
			decodeFileFormats.append(name);
		if (encode)
			encodeFileFormats.append(name);
	}
}

Codecs::Codecs(QObject* parent):
	QObject(parent)
{
    AVInputFormat *ifmt=NULL;
    AVOutputFormat *ofmt=NULL;
    URLProtocol *up=NULL;
    AVCodec *p=NULL, *p2;
    AVBitStreamFilter *bsf=NULL;
    const char *last_name;

    LibAVC::instance();//убедились что всё наместе
    printf("Codecs:\n");
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
       //  printf(
       //      " %s%s%s%s%s%s %-15s %s",
       //      decode ? "D": (/*p2->decoder ? "d":*/" "),
       //      encode ? "E":" ",
       //      type_str,
       //      cap & CODEC_CAP_DRAW_HORIZ_BAND ? "S":" ",
       //      cap & CODEC_CAP_DR1 ? "D":" ",
       //      cap & CODEC_CAP_TRUNCATED ? "T":" ",
       //      p2->name,
       //      p2->long_name ? p2->long_name : "");
       // /* if(p2->decoder && decode==0)
       //      printf(" use %s for decoding", p2->decoder->name);*/
       //  printf("\n");
	
    }

    printf("Frame size, frame rate abbreviations:\n ntsc pal qntsc qpal sntsc spal film ntsc-film sqcif qcif cif 4cif\n");
    printf("\n");
    printf(
"Note, the names of encoders and decoders do not always match, so there are\n"
"several cases where the above table shows encoder only or decoder only entries\n"
"even though both encoding and decoding are supported. For example, the h263\n"
"decoder corresponds to the h263 and h263p encoders, for file formats it is even\n"
"worse.\n");

}

QStringList 
Codecs::getAvailableCodecs(CodecType type, int coder) const
{
	QList <CodecT>::iterator c(allCodecs.begin());
	QStringList rez;

	for(; c != allCodecs.end(); c++) 
	{
		if ((c->type == type) && (coder & c->coder))
		{
			rez.append (c->name);
		}
	}
	return rez;
}

QStringList
FileFormats::getAvailableDecodeFileFormats() const
{
	return decodeFileFormats;
}

QStringList
FileFormats::getAvailableEncodeFileFormats() const
{
	return encodeFileFormats;
}



FileInfo::FileInfo(QWidget *parent)
	:QWidget(parent)
{
	tree = new QTreeWidget;
	tree->setColumnCount(2);
	tree->setHeaderItem(new QTreeWidgetItem(QStringList(tr("type")) << "value"));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget (tree);
	setLayout (layout);
}

void
FileInfo::setFilename(QString filename)
{
	LibAVC::instance();
	AVFormatContext *pFormatCtx;
	int err;
//	std::cerr << filename.toUtf8().data();
//	printf("filename : %s\n", filename.toStdString().c_str());


	if(0 != (err = av_open_input_file(&pFormatCtx, filename.toUtf8().data(), NULL, 0, NULL)))
	{
		qWarning() << "av_open_input_file" << err;
		return ;
	}
	// Retrieve stream information
	if(0 > (err = av_find_stream_info(pFormatCtx)))
	{
		qWarning() << "av_find_stream_info" ;
		return ;
	}

//	dump_format(pFormatCtx, 0, "нужный файл", 0);//for debugging
	
	tree->clear();
	QTreeWidgetItem* container =  new QTreeWidgetItem(QStringList(tr("Container")) << pFormatCtx->iformat->name);
	tree->addTopLevelItem (container);
	for(unsigned int i=0; i<pFormatCtx->nb_streams; i++) 
	{
		QString num;
		num.setNum(i);
		QStringList fields(QString(tr("Stream ")) + num);
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
		fields << buf;
		

		QTreeWidgetItem* stream = new QTreeWidgetItem(fields );
		container->addChild(stream);
	}
}

// GenericChooseFormat::GenericChooseFormat (QWidget* parent)
// 	:QWidget (parent)
// {
// }

ChooseFileFormat::ChooseFileFormat (QWidget* parent)
	:QWidget (parent)
{
	FileFormats availFormats;
	QComboBox* combobox = new QComboBox;
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(combobox);
	combobox->addItems(availFormats.getAvailableEncodeFileFormats());
	setLayout(layout);
}

QString
ChooseFileFormat::getFormat()
{
	return format;
}

void
ChooseFileFormat::setFormat(const QString text)
{
	format = text;
}
