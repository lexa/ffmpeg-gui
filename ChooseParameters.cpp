#include "ChooseParameters.hpp"



//--------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------//

EmptyChoose::EmptyChoose (QWidget* parent) 
	: QLabel(tr("choose container/codec in tree"), parent)
{
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
	if (info.length() == 0)
		return;
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
