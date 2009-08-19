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


ShowFileInfo::ShowFileInfo(QWidget* parent )
	:QWidget(parent)
{
	tree = new QTreeWidget;
	QVBoxLayout* l = new QVBoxLayout;
	tree->setColumnCount(2);
	tree->setHeaderLabels(QStringList("type") << "value");
	l->addWidget(tree);
	setLayout(l);
}

void 
ShowFileInfo::setFilename(QString filename)
{
	info = FileInfo(filename);
	
	tree->clear();
	
//	QList<QPair<CodecType, QString> >::iterator i(info.begin());
	if (info.length() == 0 ) 
		return;
	QTreeWidgetItem* container =  new QTreeWidgetItem(QStringList(tr("Container")) << info[0].second, 1000 );//FIXME сделать отображение типа контейнера
		
	for(int i=1 ; i < info.length(); i++) 
	{
		QStringList fields;
		switch (info[i].first)
		{
		case    CODEC_TYPE_UNKNOWN  : fields << "UNKNOWN"; break ;
		case    CODEC_TYPE_VIDEO : fields << "VIDEO"; break ;
		case 	CODEC_TYPE_AUDIO : fields << "AUDIO"; break ;
		case	CODEC_TYPE_DATA : fields << "DATA"; break ;
		case	CODEC_TYPE_SUBTITLE : fields << "SUBTITLE"; break ;
		case	CODEC_TYPE_NB : fields << "NB"; break ;
		default: 
			fields << "undefined type"; break ;
		}
			
		fields << info[i].second;
			
		container->addChild(new QTreeWidgetItem(fields, 1000+i));
	}
	tree->addTopLevelItem (container);
	QObject::connect (tree, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(emitCurrentItemChanged(QTreeWidgetItem*)));
}

void 
ShowFileInfo::emitCurrentItemChanged(QTreeWidgetItem* current)
{
	int id = (current->type()) - 1000;
	qWarning() << id ;
	emit currentItemChanged(info[id].first, id-1);
}

ChooseCodec::ChooseCodec (CodecType type, QWidget* parent)
	:QWidget(parent), format("copy")
{
	QComboBox* list = new QComboBox;
	Codecs availCodecs ;
	list->addItems(availCodecs.getAvailableCodecs(type, ENCODE));
	QVBoxLayout* l = new QVBoxLayout;
	l->addWidget(list);
	setLayout(l);
	QObject::connect(list, SIGNAL(activated(const QString)), this, SLOT(setFormat(const QString))); 
}

QString 
ChooseCodec::getFormat()
{
	return format;
}

void 
ChooseCodec::setFormat(const QString new_format)
{
	format=new_format;
}

EmptyChoose::EmptyChoose (QWidget* parent) 
	: QWidget(parent)
{
	new QLabel(tr("choose cpntainer/codec in tree above"), this);
}

ChooseParameters::ChooseParameters(QWidget *parent)
	:QWidget(parent)
{
	l = new QVBoxLayout;
	info = new ShowFileInfo;
	l->addWidget(info);
	currentChoose = new EmptyChoose;
	l->addWidget(currentChoose);
	setLayout(l);
	QObject::connect(info, SIGNAL(currentItemChanged(CodecType, int)), this, SLOT(changeCodecSelector(CodecType, int)));

}
void
ChooseParameters::setFilename(QString filename)
{
	info->setFilename(filename);//это нормально? это по идее слот TODO подумать: может переделать его в метод а не в слот???
	//TODO прятать инфу о кодеке
}

void
ChooseParameters::changeCodecSelector (CodecType type, int id)
{
	currentChoose = new EmptyChoose;
	
}
