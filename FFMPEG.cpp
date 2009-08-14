#include "FFMPEG.hpp"


LibAVC* LibAVC::uniqueInstance = NULL;

LibAVC* 
LibAVC::instance()
{
	if (!uniqueInstance)
		uniqueInstance = new LibAVC;
	return uniqueInstance;
}

LibAVC::LibAVC()
{
	av_register_all();
}
LibAVC::~LibAVC()
{
//	av_exit(0);//FIXME это точно нормально?
}

// void 
// getAvailableFileFormats(void)
// {
// 	AVInputFormat *ifmt=NULL;
// 	AVOutputFormat *ofmt=NULL;
// 	URLProtocol *up=NULL;
// 	AVCodec *p=NULL, *p2;
// 	AVBitStreamFilter *bsf=NULL;
// 	const char *last_name;
	
// 	LibAVC::instance();//убедились что всё наместе
	
// //	printf("File formats:\n");
// 	last_name= "000";
// 	for(;;){
// 		int decode=0;
// 		int encode=0;
// 		const char *name=NULL;
// 		const char *long_name=NULL;

// 		while((ofmt= av_oformat_next(ofmt))) {
// 			if((name == NULL || strcmp(ofmt->name, name)<0) &&
// 			   strcmp(ofmt->name, last_name)>0){
// 				name= ofmt->name;
// 				long_name= ofmt->long_name;
// 				encode=1;
// 			}
// 		}
// 		while((ifmt= av_iformat_next(ifmt))) {
// 			if((name == NULL || strcmp(ifmt->name, name)<0) &&
// 			   strcmp(ifmt->name, last_name)>0){
// 				name= ifmt->name;
// 				long_name= ifmt->long_name;
// 				encode=0;
// 			}
// 			if(name && strcmp(ifmt->name, name)==0)
// 				decode=1;
// 		}
// 		if(name==NULL)
// 			break;
// 		last_name= name;

// 		printf(
// 			" %s%s %-15s %s\n",
// 			decode ? "D":" ",
// 			encode ? "E":" ",
// 			name,
// 			long_name ? long_name:" ");
// 	}
// 	printf("\n");
// }


FileFormats::FileFormats(QObject *parent)
	:QObject(parent)
{
//	allFileFormats = getAvailableFileFormats();
	AVInputFormat *ifmt=NULL;
	AVOutputFormat *ofmt=NULL;
//	URLProtocol *up=NULL;
//	AVCodec *p=NULL, *p2;
//	AVBitStreamFilter *bsf=NULL;
	const char *last_name;
	
	LibAVC::instance();//убедились что всё наместе
	
//	printf("File formats:\n");
	last_name= "000";
	for(;;){
//		FileFormatsT tmp;
		int decode=0;
		int encode=0;
		const char *name=NULL;
		const char *long_name=NULL;

		while((ofmt= av_oformat_next(ofmt))) {
			if((name == NULL || strcmp(ofmt->name, name)<0) &&
			   strcmp(ofmt->name, last_name)>0){
				name= ofmt->name;
				long_name= ofmt->long_name;
				encode=1;
			}
		}
		while((ifmt= av_iformat_next(ifmt))) {
			if((name == NULL || strcmp(ifmt->name, name)<0) &&
			   strcmp(ifmt->name, last_name)>0){
				name= ifmt->name;
				long_name= ifmt->long_name;
				encode=0;
			}
			if(name && strcmp(ifmt->name, name)==0)
				decode = 1;

		}
		if(name==NULL)
			break;
		last_name= name;

		if (decode)
			decodeFileFormats.append(name);
		if (encode)
			encodeFileFormats.append(name);
//		allFileFormats.append(tmp);
	}
}

QStringList
FileFormats::getAvailableDecodeFileFormats() const
{
	return decodeFileFormats;
}

QStringList
FileFormats::getAvailableEncodeFileFormats() const
{
	return encodeFileFormats;
}



FileInfo::FileInfo(QObject *parent)
	:QObject(parent)
{
}

void
FileInfo::setFilename(QString filename)
{
	
}
