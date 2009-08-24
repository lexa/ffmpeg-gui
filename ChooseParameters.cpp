#include "ChooseParameters.hpp"

//--------------------------------------------------------------------------------//

EmptyChoose::EmptyChoose (int id, QWidget* parent) 
	: QLabel(tr("choose container/codec in tree"), parent)
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

	QWidget* container_tab = new ChooseFileFormat(0);
	selectors->addTab(container_tab, tr("Container"));
	scheme.insert(0, info.length());//опции для container идут последгними
	QObject::connect(container_tab, SIGNAL(parametersChanged(int, QStringList)), this, SLOT(codecParametersChanged(int, QStringList)));
	
	QHash<CodecType, int> cnt_streams;//кол-во стримов каждого типа

	for(int i=1 ; i < info.length(); i++) 
	{
		QWidget* item;
		QString name;
		switch (info[i].first)
		{
		case    CODEC_TYPE_UNKNOWN  : name = "Unknown#"; item = new EmptyChoose(i); break ;
		case    CODEC_TYPE_VIDEO : name = "Video#"; item = new ChooseVideoCodec(i); break ;
		case 	CODEC_TYPE_AUDIO : name = "Audio#"; item = new ChooseAudioCodec; break ;
		case	CODEC_TYPE_DATA : name = "Data#"; item = new EmptyChoose(i); break ;
		case	CODEC_TYPE_SUBTITLE : name = "Subtitle#"; item = new EmptyChoose(i); break ;
		case	CODEC_TYPE_NB : name = "NB#"; item = new EmptyChoose(i); break ;
		default: 
			name = "undefined type"; break ;
		}
			
		scheme.insert(i, i-1);

		QString n;
		n.setNum(cnt_streams[info[i].first]++);
		QStringList fields(name + n);
		selectors->addTab(item,  (name + n));
		QObject::connect(item, SIGNAL(parametersChanged(int, QStringList)), this, SLOT(codecParametersChanged(int, QStringList)));
//при изменении посылало сигнал дляя изменения строки опций

		fields << info[i].second;
			
		container->addChild(new QTreeWidgetItem(fields));
	}


	tree->addTopLevelItem (container);
	container->setExpanded(true);//The QTreeWidgetItem must be added to the QTreeWidget before calling this function.
}

void 
ChooseParameters::codecParametersChanged(int k , QStringList p)
{
	if (!scheme.contains(k))
	{
		qWarning() << "Internal error in codecParametersChanged";
		return;
	}
		
	int n = scheme[k];
	while (listParameters.length() <= n)
		listParameters.append (QStringList(""));

	listParameters[n] = p;
	QStringList tmp("-y"), list;
	
	tmp << "-i";
	tmp << filename;
	foreach(list, listParameters)
	{
		tmp.append(list);
	};

	qWarning() << "ffmpeg parameters : "<< tmp;
	emit parametersChanged(tmp);
}
