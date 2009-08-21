#include "StartFFmpeg.hpp"

StartFFMPEG::StartFFMPEG(QWidget* parent)
	:QTextEdit(parent)
{
//	QTextEdit* log = new QTextEdit;
	this->setReadOnly(true);
	ffmpeg = new QProcess(parent);
	QObject::connect (ffmpeg, SIGNAL(readyReadStandardError()), SLOT(readOutput()));
//	QObject::connect (ffmpeg, SIGNAL(finished()), SLOT(readOutput()));
}

void 
StartFFMPEG::parametersChanged(QStringList new_params)
{
	qWarning() << new_params;
	params = new_params;
}
void 
StartFFMPEG::start()
{
	qWarning() << "start" << params;
	ffmpeg->start("ffmpeg", params);//FIXME путь к ffmpeg надо получать при сборке
	
}

void 
StartFFMPEG::readOutput()
{
	qWarning() << "readOutput";
	this->append(QString(ffmpeg->readAllStandardError()));
}

void 
StartFFMPEG::stop()
{
	ffmpeg->kill();
}
