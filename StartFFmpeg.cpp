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
	QString tmp;
	QStringList params_without_space;
	foreach(tmp, params)
	{
		if (!tmp.isEmpty()) 
			params_without_space.append(tmp);
	}

	qWarning() << "start" << params_without_space.join("  ");
	ffmpeg->start("ffmpeg", params_without_space);//FIXME путь к ffmpeg надо получать при сборке
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

bool 
StartFFMPEG::started() const
{
	return (QProcess::Running == ffmpeg->state());
}
