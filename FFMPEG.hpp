#ifndef FFMPEG_MY_H
#define FFMPEG_MY_H

extern "C" {
#include <libavformat/avformat.h>
}


#include <QWidget>
#include <QObject>
#include <QStringList>
#include <QList>

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
	typedef struct {
		bool decode, encode : 1;
		QString name, long_name;
	} codecT;
	
	QList<codecT> allCodecs;
};

#endif //FFMPEG_MY_H
