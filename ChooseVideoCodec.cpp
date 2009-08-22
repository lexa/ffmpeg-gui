#include "ChooseVideoCodec.hpp"

ChooseVideoCodec::ChooseVideoCodec (int id, QWidget* parent)
	:QWidget(parent)
{
// 	QComboBox* list = new QComboBox;
// 	Codecs availCodecs ;
// 	list->addItems(availCodecs.getAvailableCodecs(CODEC_TYPE_VIDEO, ENCODE));
// 	QVBoxLayout* l = new QVBoxLayout;
// 	QHBoxLayout* tmp = new QHBoxLayout;
	
// 	tmp->addWidget(new QLabel(tr("Video Codec:")));
// 	tmp->addWidget(list);

// 	l->addItem(tmp);
// 	tmp = new QHBoxLayout;
	
// 	tmp->addWidget(new QLabel(tr("Size:")));
// //TODO получать доступные из ffmpeg
// 	QStringList availSizes; 
// 	availSizes << "sqcif(128x96)" << "qcif(176x144)" << "cif(352x288)" << "4cif(704x576)" << "16cif(1408x1152)" << "qqvga(160x120)" << "qvga(320x240)" << "vga(640x480)" << "svga(800x600)" << "xga(1024x768)" << "uxga(1600x1200)" << "qxga(2048x1536)" << "sxga(1280x1024)" << "qsxga(2560x2048)" << "hsxga(5120x4096)" << "wvga(852x480)" << "wxga(1366x768)" << "wsxga(1600x1024)" << "wuxga(1920x1200)" << "woxga(2560x1600)" << "wqsxga(3200x2048)" << "wquxga(3840x2400)" << "whsxga(6400x4096)" << "whuxga(7680x4800)" << "cga(320x200)" << "ega(640x350)" << "hd480(852x480)" << "hd720(1280x720)" << "hd1080(1920x1080)";
// 	QComboBox *sizes = new QComboBox;
// 	sizes->addItems(availSizes);
// 	tmp->addWidget(sizes);
	
	
// 	l->addItem(tmp);
// 	setLayout(l);
// 	QObject::connect(list, SIGNAL(activated(const QString)), this, SLOT(setFormat(const QString))); 
	this->id = id;
	ui.setupUi(this);
	Codecs availCodecs ;
	ui.video_codec->addItems(availCodecs.getAvailableCodecs(CODEC_TYPE_VIDEO, ENCODE));
	ui.video_codec->setCurrentIndex(-1);
}

void 
ChooseVideoCodec::on_video_codec_activated(const QString text)
{
	codec = text;
	emitParametersChanged();
}

void 
ChooseVideoCodec::on_size_activated(const QString text)
{
	size = text.left(text.indexOf("("));
	emitParametersChanged();
}

void 
ChooseVideoCodec::on_aspect_activated(const QString text)
{
	aspect = text;
	emitParametersChanged();
}

void 
ChooseVideoCodec::on_bitrate_valueChanged(int new_bitrate)
{
	bitrate = new_bitrate;
	emitParametersChanged();
}


void	
ChooseVideoCodec::emitParametersChanged()
{
	QStringList tmp;
	QString bitrate_s;
	bitrate_s.setNum(bitrate, 10);

	tmp << (!codec.isEmpty()?"-vcodec":"") << codec
	    << ((bitrate!=0)?"-b":"")  << ((bitrate!=0)?bitrate_s:"") 
	    << (!size.isEmpty()?"-s":"") << size
	    << (!aspect.isEmpty()?"-aspect":"") << aspect;
	emit parametersChanged(id, tmp);
}


// void 
// ChooseVideoCodec::setFormat(const QString new_format)
// {
// 	format=new_format;
// }
