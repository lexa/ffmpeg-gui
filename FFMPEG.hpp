#ifndef FFMPEG_MY_H
#define FFMPEG_MY_H

extern "C" {
#include <libavformat/avformat.h>
}


#include <QWidget>
#include <QObject>
#include <QStringList>
#include <QList>
#include <QtGlobal> 

//TODO класс singleton который будет держать ffmpeg проинициализированным
//singleton держащий ffmpeg инициализированным
class LibAVC {
public:
	static LibAVC* instance ();
private:
	static LibAVC* uniqueInstance;
protected:
	LibAVC();
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

class FileInfo : public QObject
{
	Q_OBJECT
public:
	FileInfo(QObject* parent = 0);
	void setFilename(QString);
private:

};

#endif //FFMPEG_MY_H
