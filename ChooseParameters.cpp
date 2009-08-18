#include "CodecSelection.hpp"

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
	QList<QPair<CodecType, QString> > info = FileInfo(filename);
	
	tree->clear();
	
	QTreeWidgetItem* container =  new QTreeWidgetItem(QStringList(tr("Container")) << "");//FIXME сделать отображение типа контейнера

	for(QList<QPair<CodecType, QString> >::iterator i(info.begin()) ; i != info.end(); i++) 
	{
		QStringList fields;
		switch (i->first)
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

		fields << i->second;

		container->addChild(new QTreeWidgetItem(fields));
	}

	tree->addTopLevelItem (container);
}
