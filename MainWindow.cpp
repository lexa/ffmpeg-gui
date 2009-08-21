#include "MainWindow.hpp"

#include <iostream>


void 
MainWindow::inputFileChanged(QString filename)
{	
	qWarning() << "inputFileChanged";
	layoutMain->removeWidget(params);
	delete (params);
	params = new ChooseParameters(filename);
	layoutMain->insertWidget(1, params, 1);
//	layoutMain->setStretch(1, 1);
	
}



MainWindow::MainWindow (QWidget *parent)
	:QWidget(parent)
{
	SelectionFile* inputFile = new SelectionFile(tr("Input File:"));
//	SelectionFile* outputFile = new SelectionFile(tr("Output File:"));
	QHBoxLayout* top_line = new QHBoxLayout;
	top_line->addWidget(inputFile);
//	top_line->addWidget(outputFile);
	top_line->addStretch(0);

	QObject::connect(inputFile, SIGNAL(fileChanged(QString)), this, SLOT(inputFileChanged(QString)));
//	QObject::connect(outputFile, SIGNAL(fileChanged(QString)), this, SLOT(outputFileChanged(QString)));

	params = new ChooseParameters("/home/lexa/tmp/ffmpeg/movie.avi");
//	params = new ChooseParameters("");

	layoutMain = new QVBoxLayout;

	layoutMain->addLayout(top_line);
	layoutMain->addWidget(params, 1);//FIXME убрать ???
	QPushButton* convert = new QPushButton(tr("Convert"));
	StartFFMPEG* ffmpeg = new StartFFMPEG;
	layoutMain->addWidget(convert);
	layoutMain->addWidget(ffmpeg);
//	layoutMain->setStretch(1, 1);

	setLayout(layoutMain);


	QObject::connect (convert, SIGNAL(clicked()), ffmpeg, SLOT(start())); 
	setWindowTitle(tr("ffmpeg-gui"));
}
