#include "MainWindow.hpp"

#include <iostream>


void
ChooseInputFiles::showFileDialog()
{
	QStringList files = QFileDialog::getOpenFileNames(this, label);
	
	QList<QUrl> filenames;

	// QStringList::Iterator it = files.begin();
	// while(it != files.end()) {
	// 	filenames.append(QUrl(*it));
	// 	++it;
	// }
	foreach(QString url, files) {
		filenames.append(QUrl(url));
	}

//	inputFilename->setText(files.join(","));
	emit fileChanged(filenames);
}

ChooseInputFiles::ChooseInputFiles (QString label, QWidget* parent)
	:QWidget(parent)
{
//	QLabel *inputLabel = new QLabel(label);
	this->label = label;
	
//	inputFilename = new QLineEdit;
//	inputFilename->setReadOnly(true);
	QPushButton* selectFile = new QPushButton(label);

	QHBoxLayout *layoutFile = new QHBoxLayout;
//	layoutFile->addWidget (inputLabel);
//	layoutFile->addWidget (inputFilename);
	layoutFile->addWidget (selectFile);

	QObject::connect (selectFile, SIGNAL(clicked()), this, SLOT(showFileDialog()));
//	QVBoxLayout *layoutMain = new QVBoxLayout;
//	layoutMain->addLayout(layoutFile);
	setLayout(layoutFile);
}



void 
MainWindow::inputFileChanged(QList <QUrl> filenames)
{	
	qWarning() << "inputFileChanged";
	foreach (QUrl file, filenames)
		params->addUrl(file);
}



MainWindow::MainWindow (QWidget *parent)
	:QWidget(parent)
{
//	inputFile = new SelectionFile();
	ChooseInputFiles* addInputFiles = new ChooseInputFiles(tr("add files"));
	QPushButton* clear = new QPushButton(tr("clear filelist"));
	QHBoxLayout* top_line = new QHBoxLayout;
	top_line->addWidget(addInputFiles);
	top_line->addWidget(clear);
	top_line->addStretch(0);

//	params = new ChooseParameters("/home/lexa/tmp/ffmpeg/movie.avi");
	params = new ChooseParameters;
	layoutMain = new QVBoxLayout;

	layoutMain->addLayout(top_line);
	layoutMain->addWidget(params, 1);
	convert_button = new QPushButton(tr("Convert"));
	ffmpeg = new StartFFMPEG;
	layoutMain->addWidget(convert_button);
	layoutMain->addWidget(ffmpeg);
//	layoutMain->setStretch(1, 1);


	setLayout(layoutMain);

	QObject::connect (addInputFiles, SIGNAL(fileChanged(QList<QUrl>)), this, SLOT(inputFileChanged(QList<QUrl>)));
	QObject::connect (clear, SIGNAL(clicked()), params, SLOT(clear()));
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
//	inputFile->fileDropped(event->mimeData()->urls());
	inputFileChanged(event->mimeData()->urls());

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
