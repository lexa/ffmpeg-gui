#include "ChooseParameters.hpp"

//--------------------------------------------------------------------------------//

EmptyChoose::EmptyChoose ( QWidget* parent) 
	: GenericChoose(parent)
{
}
//--------------------------------------------------------------------------------//

ChooseParameters::ChooseParameters(QString filename, QWidget *parent)
	:QSplitter(parent)
{
	this->filename=filename;
	tree = new QTreeWidget;
	tree->setColumnCount(2);
	tree->setHeaderLabels(QStringList("type") << "value");
	this->addWidget(tree);
	QTabWidget* selectors = new QTabWidget;
	this->addWidget(selectors);

 	QList<QPair<CodecType, QString> > info = FileInfo(filename);
	if (info.length() == 0)
		return;
	QTreeWidgetItem* container = new QTreeWidgetItem(QStringList(tr("Container")) << info[0].second);

	GenericChoose* container_tab = new ChooseFileFormat;
	selectors->addTab(container_tab, tr("Container"));
//	scheme.insert(0, info.length());//опции для container идут последгними
//	QObject::connect(container_tab, SIGNAL(parametersChanged(int, QStringList)), this, SLOT(codecParametersChanged(int, QStringList)));
	
	for(int i=1 ; i < info.length(); i++) 
	{
		QString name;
		GenericChoose*  item;
		switch (info[i].first)
		{
		case    CODEC_TYPE_UNKNOWN  : name = "Unknown#"; item = new EmptyChoose; break ;
		case    CODEC_TYPE_VIDEO : name = "Video#"; item = new ChooseVideoCodec; break ;
		case 	CODEC_TYPE_AUDIO : name = "Audio#"; item = new ChooseAudioCodec; break ;
		case	CODEC_TYPE_DATA : name = "Data#"; item = new EmptyChoose; break ;
		case	CODEC_TYPE_SUBTITLE : name = "Subtitle#"; item = new EmptyChoose; break ;
		case	CODEC_TYPE_NB : name = "NB#"; item = new EmptyChoose; break ;
		default: 
			name = "undefined type"; break ;
		}
			
//		scheme.insert(i, i-1);

		QString n;
		n.setNum(cnt_streams[info[i].first]++);
		QStringList fields(name + n);
		selectors->addTab(item,  (name + n));
		built_widgets.append(item);
//		QObject::connect(item, SIGNAL(parametersChanged(int, QStringList)), this, SLOT(codecParametersChanged(int, QStringList)));
//при изменении посылало сигнал дляя изменения строки опций

		fields << info[i].second;
			
		container->addChild(new QTreeWidgetItem(fields));
	}

	built_widgets.append(container_tab);

	tree->addTopLevelItem (container);
	container->setExpanded(true);//The QTreeWidgetItem must be added to the QTreeWidget before calling this function.
}

QStringList 
ChooseParameters::getParams()
{
	QStringList tmp, list;
	tmp << "-i";
	tmp << filename;
	GenericChoose* w;
	foreach (w, built_widgets) 
	{
		tmp.append(w->getParams());
	}
	int i=1;
	while (cnt_streams[CODEC_TYPE_VIDEO] > i) 
	{
		tmp.append("-newvideo");
		i++;
	}
	i=1;
	while (cnt_streams[CODEC_TYPE_AUDIO] > i) 
	{
		tmp.append("-newaudio");
		i++;
	}

	qWarning() << "ffmpeg parameters : "<< tmp;
//	emit parametersChanged(tmp);
	return tmp;
}
