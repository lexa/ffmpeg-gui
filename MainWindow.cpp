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

MainWindow::MainWindow (QWidget *parent)
	:QWidget(parent)
{
//	inputFileName = new SelectionInputFile();

	ChooseParameters *params = new ChooseParameters("/home/lexa/tmp/ffmpeg/movie.avi");

	QVBoxLayout *layoutMain = new QVBoxLayout;
//	layoutMain->addWidget(inputFileName);
	layoutMain->addWidget(params);
	layoutMain->addWidget(new QPushButton(tr("Convert")));
	setLayout(layoutMain);

//	QObject::connect (inputFileName, SIGNAL(inputFileChanged(QString)), params, SLOT(setFilename(QString))); 
	setWindowTitle(tr("ffmpeg-gui"));
}
