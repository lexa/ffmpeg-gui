#include "MainWindow.hpp"

#include <iostream>


void 
MainWindow::inputFileChanged(QList <QUrl> filenames)
{	
	qWarning() << "inputFileChanged";
	layoutMain->removeWidget(params);
	delete (params);
	params = new ChooseParameters(filenames);
	layoutMain->insertWidget(1, params, 1);
//	QObject::connect (params, SIGNAL(parametersChanged(QStringList)), ffmpeg, SLOT(parametersChanged(QStringList))); 
//	layoutMain->setStretch(1, 1);
	
}



MainWindow::MainWindow (QWidget *parent)
	:QWidget(parent)
{
	inputFile = new SelectionFile(tr("Input File:"));
//	SelectionFile* outputFile = new SelectionFile(tr("Output File:"));
	QHBoxLayout* top_line = new QHBoxLayout;
	top_line->addWidget(inputFile);
//	top_line->addWidget(outputFile);
	top_line->addStretch(0);

//	QObject::connect(outputFile, SIGNAL(fileChanged(QString)), this, SLOT(outputFileChanged(QString)));

//	params = new ChooseParameters("/home/lexa/tmp/ffmpeg/movie.avi");
	QList<QUrl> tmp;
	params = new ChooseParameters(tmp);
	layoutMain = new QVBoxLayout;

	layoutMain->addLayout(top_line);
	layoutMain->addWidget(params, 1);//FIXME убрать ???
	convert_button = new QPushButton(tr("Convert"));
	ffmpeg = new StartFFMPEG;
	layoutMain->addWidget(convert_button);
	layoutMain->addWidget(ffmpeg);
//	layoutMain->setStretch(1, 1);


	setLayout(layoutMain);

	QObject::connect (inputFile, SIGNAL(fileChanged(QList<QUrl>)), this, SLOT(inputFileChanged(QList<QUrl>)));
	QObject::connect (convert_button, SIGNAL(clicked()), this, SLOT(start_ffmpeg())); 
	QObject::connect (ffmpeg, SIGNAL(stopped(int)), this, SLOT(ffmpeg_stopped())); 
	setWindowTitle(tr("ffmpeg-gui"));

	setAcceptDrops(true);//разрешили перетаскивать
}


void 
MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	qWarning() << (event->mimeData()->formats()) ;
	
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}


void MainWindow::dropEvent(QDropEvent *event)
{
	qWarning() << event->mimeData()->text();
	inputFile->fileDropped(event->mimeData()->urls());

//	if (event->mimeData()->hasFormat("text/uri-list"))
//		event->acceptProposedAction();
		}

void
MainWindow::ffmpeg_stopped()

{
	convert_button->setText(tr("Start ffmpeg"));
}

void 
MainWindow::start_ffmpeg()
{
	if (ffmpeg->started())
	{
		ffmpeg->stop();
		qWarning() << "stop ffmpeg";
	} else {
		ffmpeg->parametersChanged(params->getParams());
		ffmpeg->start();
		convert_button->setText(tr("Stop ffmpeg"));
		qWarning() << "start ffmpeg";
	}
}
