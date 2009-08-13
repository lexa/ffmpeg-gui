#include "MainWindow.hpp"

#include <iostream>



// FileInfo::FileInfo (QWidget *parent)
// 	:QWidget(parent)
// {
// 	mainTree = new QTreeWidget();
// 	mainTree->clear();
// 	mainTree->setHeaderLabels(QStringList(tr("streams")));
// 	QVBoxLayout* layout =new QVBoxLayout();
// 	layout->addWidget(mainTree);
// 	setLayout(layout);
// }

// void
// FileInfo::updateInfo(QString filename)
// {
// //	qWarning() << "updateInfo";
// 	AVFormatContext *pFormatCtx=NULL;
// 	int err;
// 	avcodec_register_all();
// 	avdevice_register_all();
// 	av_register_all();
// 	//хз почему но именно так работет FIXME проверку на ощибку

// 	if (0 != (err = av_open_input_file(&pFormatCtx, filename.toStdString().c_str(), NULL, 0, NULL)))
// 	{
// 		qWarning() << "av_open_input_file" << err;
// 		return ;
// 	}
// 	if (0 > (err = av_find_stream_info(pFormatCtx)))
// 	{
// 		qWarning() << "av_find_stream_info" << err;
// 		av_close_input_file(pFormatCtx);
// 		return;
// 	}

// //	dump_format(pFormatCtx, 0, filename.toStdString().c_str(), false);
// 	mainTree->clear();
	
// 	for(int i=0; i<pFormatCtx->nb_streams; i++) {
// 		char buf[256];
// 		avcodec_string(buf, sizeof(buf), pFormatCtx->streams[i]->codec, false);
// 		mainTree->addTopLevelItem(new QTreeWidgetItem(QStringList(buf)));
// 	}
// }



void
SelectionInputFile::showChooseInputFileDialog()
{
//	std::cerr << "file dialog" << std::endl;
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"));
//	qWarning() << filename ;

	inputFilename->setText(filename);
//	std::cerr << "end" << std::endl;
}


void 
SelectionInputFile::emitInputFileChanged ()
{
	emit inputFileChanged(inputFilename->text());
}

SelectionInputFile::SelectionInputFile (QWidget* parent)
	:QWidget(parent)
{
	QLabel *inputLabel = new QLabel(tr("Input File:"));
	
	inputFilename = new QLineEdit("/home/lexa/tmp/ffmpeg/movie.avi");
	QPushButton* selectInputFile = new QPushButton(tr("Select File"));

	QHBoxLayout *layoutInputFile = new QHBoxLayout;
	layoutInputFile->addWidget (inputLabel);
	layoutInputFile->addWidget (inputFilename );
	layoutInputFile->addWidget (selectInputFile);

	QObject::connect (selectInputFile, SIGNAL(clicked()), this, SLOT(showChooseInputFileDialog()) );//переипсать  на немодальные окна
	QObject::connect (inputFilename, SIGNAL(textChanged(QString)), this, SLOT(emitInputFileChanged()) );
	QVBoxLayout *layoutMain = new QVBoxLayout;
	layoutMain->addLayout(layoutInputFile);
	setLayout(layoutMain);

}

SelectionOutputContainer::SelectionOutputContainer(QWidget *parent)
	:QWidget(parent)
{
//	qWarning() << getAvailableFormats();
}

MainWindow::MainWindow (QWidget *parent)
	:QWidget(parent)
{
	inputFileName = new SelectionInputFile();
//	FileInfo *inputFile = new FileInfo;
	SelectionOutputContainer* outputContainer = new SelectionOutputContainer;

	QVBoxLayout *layoutMain = new QVBoxLayout;
	layoutMain->addWidget(inputFileName);
//	layoutMain->addWidget(inputFile);
	layoutMain->addWidget(outputContainer);
	layoutMain->addWidget(new QPushButton("111"));
	setLayout(layoutMain);
	
//	QObject::connect (inputFileName, SIGNAL(inputFileChanged(QString)), inputFile, SLOT(updateInfo(QString))); 
//	new Codecs;
	setWindowTitle(tr("ffmpeg-gui"));
}
