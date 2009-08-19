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

// QString 
// ChooseCodec::getFormat()
// {
// 	return format;
// }

void 
ChooseCodec::setFormat(const QString new_format)
{
	format=new_format;
}
//--------------------------------------------------------------------------------//

EmptyChoose::EmptyChoose (QWidget* parent) 
	: QWidget(parent)
{
	new QLabel(tr("choose cpntainer/codec in tree above"), this);
}
//--------------------------------------------------------------------------------//

ChooseParameters::ChooseParameters(QWidget *parent)
	:QWidget(parent)
{
	l = new QVBoxLayout;
	tree = new QTreeWidget;
	tree->setColumnCount(2);
	tree->setHeaderLabels(QStringList("type") << "value");
	l->addWidget(tree);

	currentChoose = new EmptyChoose;

	l->addWidget(currentChoose);
	setLayout(l);

	QObject::connect (tree, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(currentItemChanged(QTreeWidgetItem*)));

}
void
ChooseParameters::setFilename(QString filename)
{
 	QList<QPair<CodecType, QString> > info = FileInfo(filename);
	
	tree->clear();

	for(QList<QWidget *>::iterator i(codecOptions.begin()); i != codecOptions.end(); i++ )
	{
		l->removeWidget(*i);
		delete (*i);
	}
	codecOptions.clear();
	currentChoose = NULL;
	
	if (info.length() == 0)
		return;

	QTreeWidgetItem* container = new QTreeWidgetItem(QStringList(tr("Container")) << info[0].second, 1000 );

	QWidget* item = new ChooseFileFormat;
	item->hide();
	l->addWidget(item);

//	codecParametersChanged

	codecOptions.append(item);
	 
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
			
		QWidget* item = new ChooseCodec (info[i].first);
		item->hide();
		l->addWidget(item);

		fields << info[i].second;
			
		container->addChild(new QTreeWidgetItem(fields, 1000+i));
		
		codecOptions.append(item);
	}

	tree->addTopLevelItem (container);
}


void 
ChooseParameters::currentItemChanged(QTreeWidgetItem* current)
{
	if (current == NULL)
		return ;

	if (NULL != currentChoose)
		currentChoose->hide();

	int id = (current->type()) - 1000;
	currentChoose = codecOptions[id];
	currentChoose->show();
}
