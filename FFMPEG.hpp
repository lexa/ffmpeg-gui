#ifndef FFMPEG_MY_H
#define FFMPEG_MY_H


#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif


extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


#include "Global.hpp"
#include "Utils.hpp"
#include <QDataStream>
#include <QString>
#include <QStringList>

//singleton держащий libffmpeg инициализированным
class LibAVC :public Singleton<LibAVC>
{
protected:
	LibAVC(void);
	LibAVC* operator=(LibAVC*);
	virtual ~LibAVC(void);
	friend class Singleton<LibAVC>;
};

QStringList operator<<(QStringList, CodecType);


//typedef Singleton<LibAVC> LibAVC;


#endif //FFMPEG_MY_H
