#include "ChooseParameters.hpp"

//--------------------------------------------------------------------------------//

EmptyChoose::EmptyChoose ( QWidget* parent) 
	: GenericChoose(parent)
{
}
//--------------------------------------------------------------------------------//

ChooseParameters::ChooseParameters(QList<QUrl> filenames, QWidget *parent)
	:QSplitter(parent)
{
	this->filenames=filenames;
	tree = new QTreeWidget;
	tree->setColumnCount(2);
	tree->setHeaderLabels(QStringList("type") << "value");
	this->addWidget(tree);
	QTabWidget* selectors = new QTabWidget;
	this->addWidget(selectors);

	GenericChoose* container_tab = new ChooseFileFormat;
	selectors->addTab(container_tab, tr("Container"));

	QUrl name;
	FileInfo* info;
	int filenum = 0;
	foreach (name, filenames)
	{
		try{
			info = new FileInfo (name);
		}
		catch (QString err) {
			qWarning() << err << name;
			continue;
		}

		QTreeWidgetItem* container = new QTreeWidgetItem(QStringList(name.toString()) << info->container());

		QList<QPair<CodecType, QString> > streams = info->getStreams();
	
		for(int i=0 ; i < streams.length(); i++ )
		{
			QString name;
			GenericChoose*  item;
			switch (streams[i].first)
			{
			case    CODEC_TYPE_UNKNOWN  : name = "Unknown "; item = new EmptyChoose; break ;
			case    CODEC_TYPE_VIDEO : name = "Video "; item = new ChooseVideoCodec; break ;
			case 	CODEC_TYPE_AUDIO : name = "Audio "; item = new ChooseAudioCodec; break ;
			case	CODEC_TYPE_DATA : name = "Data "; item = new EmptyChoose; break ;
			case	CODEC_TYPE_SUBTITLE : name = "Subtitle "; item = new EmptyChoose; break ;
			case	CODEC_TYPE_NB : name = "NB#"; item = new EmptyChoose; break ;
			default: 
				name = "undefined type"; break ;
			}
			
			QString b(name + num_to_string((cnt_streams[streams[i].first])++));
			QStringList fields(b);
			selectors->addTab(item, b);
			built_widgets.append(item);
			
			fields << streams[i].second;
			container->addChild(new QTreeWidgetItem(fields));
		}
			    
		tree->addTopLevelItem (container);
		container->setExpanded(true);
		delete (info);
		filenum++;
	}
	built_widgets.append(container_tab);
}

QStringList 
ChooseParameters::getParams()
{
	QStringList tmp, list;

	foreach (QUrl url, filenames) 
	{
		tmp << "-i";
		tmp << url.toString();
	}

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
