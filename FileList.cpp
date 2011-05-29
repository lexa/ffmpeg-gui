
#include "FileList.hpp"


//////////////////////////////////////////////////////////////////

namespace GUI
{

	FileList::FileList(QWidget *parent )
		: QTreeWidget(parent)
	{
//		setColumnCount(3);
		setAcceptDrops(true);//accept dropped files
		// setHeaderLabels (QStringList() << "type" << "value"  );
		
		setColumnCount ( 3 );
		setHeaderLabel("1zzz");
		setHeaderLabel("2zzz");
		setHeaderLabel("3zzz");

		qDebug() << columnCount();
	}

	void 
	FileList::dragEnterEvent(QDragEnterEvent* event)
	{
		if ( event->mimeData()->hasFormat("text/uri-list"))
			event->acceptProposedAction();
		qDebug() << "EnterEvent" << event->mimeData()->text() << event->mimeData()->hasFormat("text/uri-list");
	}

	void 
	FileList::dragMoveEvent(QDragMoveEvent *event)
	{
		event->acceptProposedAction();//TODO а тут проверка mime не нужна?
	}

	void 
	FileList::dropEvent(QDropEvent *event)
	{
		add_file(event->mimeData()->text());
		event->acceptProposedAction();
//		qDebug() << "dropEvent" << event->mimeData()->formats();
	}
	void 
	FileList::add_file(QString path)
	{
		FileInfo info (path);
//		QStringList toplevel_msg = (QStringList() << str1 << str2 << str3);
		QTreeWidgetItem* toplevel = new QTreeWidgetItem(this, QStringList(path) << "file" << "", QTreeWidgetItem::Type);
		CodecStringPair tracks=info.getStreams();

		QPair<CodecType, QString> t;
		foreach (t, tracks)
		{
			new QTreeWidgetItem(toplevel, QStringList() << t.first << t.second );
		}
	}
	

}



QString
FileInfo::container() const
{
	return container_;
}


FileInfo::FileInfo(QString filename)
{
	LibAVC::Instance(); //просто убедится что проинициализирован

//	Singleton<int>::instance();

	AVFormatContext *pFormatCtx;
	int err;
//	QList<QPair<CodecType, QString> > rez;

	if(0 != (err = av_open_input_file(&pFormatCtx, filename.toUtf8().data(), NULL, 0, NULL)))
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
FileInfo::getStreams() const
{
	return streams;
}
