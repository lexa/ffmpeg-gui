#ifndef START_FFMPEG_H_
#define START_FFMPEG_H_

#include <QWidget>
#include <QTextEdit>
#include <QProcess>
#include <QDebug>

class StartFFMPEG 
	:public QTextEdit
{
	Q_OBJECT
public:
 	StartFFMPEG(QWidget* parent = 0);
	bool started() const;
signals:
	void stopped(int);
public slots:
	void parametersChanged(QStringList);
	void start();
	void stop();
private slots:
	void readOutput();
private:
	QProcess* ffmpeg;
	QStringList params;
};


#endif
