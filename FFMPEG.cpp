#include "FFMPEG.hpp"


// LibAVC* LibAVC::uniqueInstance = NULL;

// LibAVC* 
// LibAVC::instance()
// {
// 	if (!uniqueInstance)
// 		uniqueInstance = new LibAVC;
// 	return uniqueInstance;
// }


LibAVC::LibAVC(void )
{
	av_register_all();
}
LibAVC::~LibAVC(void)
{
//	av_exit(0);//FIXME это точно нормально?
}


QStringList
operator<<(QStringList src, CodecType ct)
{
	switch ( ct )
	{
	case CODEC_TYPE_UNKNOWN: src << "unknown"; break ;
	case CODEC_TYPE_VIDEO: src << "video"; break;
	case CODEC_TYPE_AUDIO: src << "audio";
	case CODEC_TYPE_DATA: src << "data"; break ; 
	case CODEC_TYPE_SUBTITLE: src << "subtitle"; break ; 
	case CODEC_TYPE_ATTACHMENT: src << "attachment"; break ; 
	case CODEC_TYPE_NB: src << "nb"; break ; 
	default:
		src << "UNKONWN CODEC TYPE";
	}
	return src;
}
