#include "ChooseParameters.hpp"

ChooseFileFormat::ChooseFileFormat (QWidget* parent)
	:QWidget (parent)
{
	FileFormats availFormats;
	QComboBox* combobox = new QComboBox;
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(combobox);
	combobox->addItems(availFormats.getAvailableEncodeFileFormats());
	QObject::connect(combobox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(setFormat(const QString)));
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


//--------------------------------------------------------------------------------//

ChooseVideoCodec::ChooseVideoCodec (QWidget* parent)
	:QWidget(parent), format("copy")
{
	QComboBox* list = new QComboBox;
	Codecs availCodecs ;
	list->addItems(availCodecs.getAvailableCodecs(CODEC_TYPE_VIDEO, ENCODE));
	QVBoxLayout* l = new QVBoxLayout;
	QHBoxLayout* tmp = new QHBoxLayout;
	
	tmp->addWidget(new QLabel(tr("Video Codec:")));
	tmp->addWidget(list);

	l->addItem(tmp);
	tmp = new QHBoxLayout;
	
	tmp->addWidget(new QLabel(tr("Size:")));
//TODO получать доступные из ffmpeg
	QStringList availSizes; 
	availSizes << "sqcif(128x96)" << "qcif(176x144)" << "cif(352x288)" << "4cif(704x576)" << "16cif(1408x1152)" << "qqvga(160x120)" << "qvga(320x240)" << "vga(640x480)" << "svga(800x600)" << "xga(1024x768)" << "uxga(1600x1200)" << "qxga(2048x1536)" << "sxga(1280x1024)" << "qsxga(2560x2048)" << "hsxga(5120x4096)" << "wvga(852x480)" << "wxga(1366x768)" << "wsxga(1600x1024)" << "wuxga(1920x1200)" << "woxga(2560x1600)" << "wqsxga(3200x2048)" << "wquxga(3840x2400)" << "whsxga(6400x4096)" << "whuxga(7680x4800)" << "cga(320x200)" << "ega(640x350)" << "hd480(852x480)" << "hd720(1280x720)" << "hd1080(1920x1080)";
	QComboBox *sizes = new QComboBox;
	sizes->addItems(availSizes);
	tmp->addWidget(sizes);
	
	
	l->addItem(tmp);
	setLayout(l);
	QObject::connect(list, SIGNAL(activated(const QString)), this, SLOT(setFormat(const QString))); 
}


void 
ChooseVideoCodec::setFormat(const QString new_format)
{
	format=new_format;
}
//--------------------------------------------------------------------------------//

ChooseAudioCodec::ChooseAudioCodec (QWidget* parent)
	:QWidget(parent), format("copy")
{
	QComboBox* list = new QComboBox;
	Codecs availCodecs ;
	list->addItems(availCodecs.getAvailableCodecs(CODEC_TYPE_AUDIO, ENCODE));
	QVBoxLayout* l = new QVBoxLayout;
	QHBoxLayout* tmp = new QHBoxLayout;
	
	tmp->addWidget(new QLabel(tr("Audio Codec:")));
	tmp->addWidget(list);
	
	l->addItem(tmp);
	setLayout(l);
	QObject::connect(list, SIGNAL(activated(const QString)), this, SLOT(setFormat(const QString))); 
}


void 
ChooseAudioCodec::setFormat(const QString new_format)
{
	format=new_format;
}

//--------------------------------------------------------------------------------//

EmptyChoose::EmptyChoose (QWidget* parent) 
	: QWidget(parent)
{
//	new QLabel(tr("choose cpntainer/codec in tree above"), this);
}
//--------------------------------------------------------------------------------//

ChooseParameters::ChooseParameters(QString filename, QWidget *parent)
	:QSplitter(parent)
{
	tree = new QTreeWidget;
	tree->setColumnCount(2);
	tree->setHeaderLabels(QStringList("type") << "value");
	addWidget(tree);
	QTabWidget* selectors = new QTabWidget;
	addWidget(selectors);

 	QList<QPair<CodecType, QString> > info = FileInfo(filename);
	QTreeWidgetItem* container = new QTreeWidgetItem(QStringList(tr("Container")) << info[0].second);

	selectors->addTab(new ChooseFileFormat, tr("Container"));

	
	QHash<CodecType, int> cnt_streams;//кол-во стримов каждого типа

	for(int i=1 ; i < info.length(); i++) 
	{
		QWidget* item;
		QString name;
		switch (info[i].first)
		{
		case    CODEC_TYPE_UNKNOWN  : name = "Unknown"; item = new EmptyChoose; break ;
		case    CODEC_TYPE_VIDEO : name = "Video"; item = new ChooseVideoCodec; break ;
		case 	CODEC_TYPE_AUDIO : name = "Audio"; item = new ChooseAudioCodec; break ;
		case	CODEC_TYPE_DATA : name = "Data"; item = new EmptyChoose; break ;
		case	CODEC_TYPE_SUBTITLE : name = "Subtitle"; item = new EmptyChoose; break ;
		case	CODEC_TYPE_NB : name = "NB"; item = new EmptyChoose; break ;
		default: 
			name = "undefined type"; break ;
		}
			
		QStringList fields(name);

		QString n;
		n.setNum(cnt_streams[info[i].first]++);
		selectors->addTab(item,  (name + (tr(" #")) + n));
		QObject::connect(item, SIGNAL(parametersChanged(int, QString)), this, SLOT(codecParametersChanged(int, QString)));
//FIXME дописать чтоб изменения посылало сигнал дляя изменения строки опций

		fields << info[i].second;
			
		container->addChild(new QTreeWidgetItem(fields));
		
	}

	tree->addTopLevelItem (container);
	container->setExpanded(true);//The QTreeWidgetItem must be added to the QTreeWidget before calling this function.


}

void 
ChooseParameters::codecParametersChanged(int n , QString p)
{
	while (listParameters.length() < n)
		listParameters.append ("");

	listParameters[n] = p;
	QStringList tmp(listParameters);
	emit parametersChanged(tmp.join("    "));
}
