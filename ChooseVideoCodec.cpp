#include "ChooseVideoCodec.hpp"

ChooseVideoCodec::ChooseVideoCodec (QWidget* parent)
	:GenericChoose(parent)
{
	ui.setupUi(this);
	Codecs availCodecs ;
	ui.video_codec->addItems(availCodecs.getAvailableCodecs(CODEC_TYPE_VIDEO, ENCODE));
	ui.video_codec->setCurrentIndex(-1);
	bitrate = max_bitrate = min_bitrate = 0;
}

void 
ChooseVideoCodec::on_max_bitrate_valueChanged(int value)
{
	max_bitrate = value;
	// if (bitrate > max_bitrate)
	// 	ui.bitrate->setValue(max_bitrate);
//	emitParametersChanged();
}

void 
ChooseVideoCodec::on_min_bitrate_valueChanged(int value)
{
	min_bitrate = value;
	// if (bitrate < min_bitrate)
	// 	ui.bitrate->setValue(min_bitrate);
//	emitParametersChanged();
}


void 
ChooseVideoCodec::on_video_codec_activated(const QString text)
{
	codec = text;
//	emitParametersChanged();
}

void 
ChooseVideoCodec::on_size_activated(const QString text)
{
	size = text.left(text.indexOf("("));
//	emitParametersChanged();
}

void 
ChooseVideoCodec::on_aspect_activated(const QString text)
{
	aspect = text;
//	emitParametersChanged();
}

void 
ChooseVideoCodec::on_bitrate_valueChanged(int new_bitrate)
{
	bitrate = new_bitrate;
	if (min_bitrate > bitrate) 
		ui.min_bitrate->setValue(bitrate);
	if (max_bitrate < bitrate) 
		ui.max_bitrate->setValue(bitrate);
//	emitParametersChanged();
}


QStringList
ChooseVideoCodec::getParams() const
{
	QStringList tmp;

	tmp << "-vcodec" << (codec.isEmpty()?"copy":codec)
	    << check_not_null(bitrate*1000, "-b") 
	    << check_not_null(max_bitrate*1024, "-maxrate")
	    << check_not_null(min_bitrate*1024, "-minrate")
	    << ((bitrate!=0)?"-bufsize":"") << ((bitrate!=0)?"6000k":"") //FIXME нормальное определение bufsize
	    << (!size.isEmpty()?"-s":"") << size
	    << (!aspect.isEmpty()?"-aspect":"") << aspect;
	return tmp;
}


// void 
// ChooseVideoCodec::setFormat(const QString new_format)
// {
// 	format=new_format;
// }
