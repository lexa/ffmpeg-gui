#include <iostream>
//#include <QApplication>

extern "C" {
#include <libavformat/avformat.h>
}


void available_file_formats(void)
{
    AVInputFormat *ifmt=NULL;
    AVOutputFormat *ofmt=NULL;
    URLProtocol *up=NULL;
    AVCodec *p=NULL, *p2;
    AVBitStreamFilter *bsf=NULL;
    const char *last_name;

    printf("File formats:\n");
    last_name= "000";
    for(;;){
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
                decode=1;
        }
        if(name==NULL)
            break;
        last_name= name;

        printf(
            " %s%s %-15s %s\n",
            decode ? "D":" ",
            encode ? "E":" ",
            name,
            long_name ? long_name:" ");
    }
    printf("\n");
}


// int main(int argc, char *argv[])
// {
// 	avcodec_register_all();
// //	avdevice_register_all();
// 	av_register_all();

// 	// for(int i=0; i<CODEC_TYPE_NB; i++){
// 	// 	avctx_opts[i]= avcodec_alloc_context2(i);
// 	// }
// 	// avformat_opts = avformat_alloc_context();

// 	available_file_formats();

// 	return av_exit(0);
// }
