#include "ChooseParameters.hpp"

//--------------------------------------------------------------------------------//

EmptyChoose::EmptyChoose ( QWidget* parent) 
	: GenericChoose(parent)
{
}
//--------------------------------------------------------------------------------//

void 
ChooseParameters::clear()
{
	filenum = 0;
 	tree->clear();
	filenames.clear();
	built_widgets.clear();
	selectors->clear();
	selectors->addTab(container_tab, tr("Container"));
	cnt_streams.clear();

}

void 
ChooseParameters::addUrl(QUrl url)
{
	filenames.append(url);
	try
	{
		FileInfo info(url);

		QMap<CodecType, int> streams_in_file;//кол-во стримов каждого типа
			
		QTreeWidgetItem* container_tree = new QTreeWidgetItem(QStringList(url.toString()) << info.container());
		
		QList<QPair<CodecType, QString> > streams = info.getStreams();

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
			
			QString b(name + num_to_string(filenum) + ":" + num_to_string((streams_in_file[streams[i].first])++));
			QStringList fields(b);

			selectors->addTab(item, b);
			built_widgets.append(item);
			
			fields << streams[i].second;
			container_tree->addChild(new QTreeWidgetItem(fields));

			tree->addTopLevelItem (container_tree);
			container_tree->setExpanded(true);
			(cnt_streams[streams[i].first])++;
		}
		filenum++;
	}
	catch (QString err)
	{
		tree->addTopLevelItem (new QTreeWidgetItem(QStringList(url.toString()) << err));
	}

}

ChooseParameters::ChooseParameters(QWidget *parent)
	:QSplitter(parent)
{
	tree = new QTreeWidget;
	tree->setColumnCount(2);
	tree->setHeaderLabels(QStringList("type") << "value");
	this->addWidget(tree);
	selectors = new QTabWidget;
	this->addWidget(selectors);

	container_tab = new ChooseFileFormat;
	selectors->addTab(container_tab, tr("Container"));



	filenum = 0;
//--end--here--
//	built_widgets.append(container_tab);
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
		tmp << (w->getParams());
	}
	tmp << container_tab->getParams();

	int i=1;
	while (cnt_streams[CODEC_TYPE_VIDEO] > i) 
	{
		tmp << ("-newvideo");
		i++;
	}
	i=1;
	while (cnt_streams[CODEC_TYPE_AUDIO] > i) 
	{
		tmp << ("-newaudio");
		i++;
	}


	qWarning() << "ffmpeg parameters : "<< tmp;
//	emit parametersChanged(tmp);
	return tmp;
}
