#ifndef FFMPEG_MY_H
#define FFMPEG_MY_H

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


#include <QWidget>
#include <QObject>
#include <QStringList>
#include <QList>
#include <QtGlobal> 
#include <QtGlobal>
#include <QtDebug>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QTreeWidgetItem>

#include <iostream>


//TODO класс singleton который будет держать ffmpeg проинициализированным
//singleton держащий ffmpeg инициализированным
class LibAVC {
public:
	static LibAVC* instance ();
private:
	static LibAVC* uniqueInstance;
protected:
	LibAVC();
	LibAVC(LibAVC*);
	LibAVC* operator=(LibAVC*);
	~LibAVC();
	
};


class FileFormats : public QObject
{
	Q_OBJECT
public:
	FileFormats(QObject* parent = 0);
	QStringList getAvailableDecodeFileFormats() const;
	QStringList getAvailableEncodeFileFormats() const;
private:
	// typedef struct {
	// 	bool decode, encode : 1;
	// 	QString name, long_name;
	// } FileFormatsT;
	
	QStringList encodeFileFormats;
	QStringList decodeFileFormats;
};

//TODO реализовать
class Codecs : public QObject
{
	Q_OBJECT
};

//виджет отображающий информацию о файле
class FileInfo : 
	public QWidget
{
	Q_OBJECT
public:
	FileInfo(QWidget* parent = 0);
public slots:
	void setFilename(QString);
private:
	QTreeWidget *tree;
};

#endif //FFMPEG_MY_H
