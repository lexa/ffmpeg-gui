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
#include <QComboBox>
#include <QPair>

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

enum Appointment {DECODE=1, ENCODE=2};
class Codecs : public QObject
{
	Q_OBJECT
	
public:
	Codecs(QObject* parent = 0);
//	enum CodecType {CODEC_TYPE_SUBTITLE CODEC_TYPE_VIDEO CODEC_TYPE_AUDIO}
	QStringList getAvailableCodecs(CodecType type, int coder /* Appointment*/) const;
private:
	struct CodecT {
		CodecType type;
		int coder;//Appointment
		QString name;
	};
	mutable QList <CodecT> allCodecs;
};


QList<QPair<CodecType, QString> > FileInfo(QString filename);

#endif //FFMPEG_MY_H
