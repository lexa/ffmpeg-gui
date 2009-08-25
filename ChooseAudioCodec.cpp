#include "ChooseAudioCodec.hpp"

ChooseAudioCodec::ChooseAudioCodec (QWidget* parent)
	:GenericChoose(parent)
{
	ui.setupUi(this);
	Codecs availCodecs ;
	ui.audio_codec->addItems(availCodecs.getAvailableCodecs(CODEC_TYPE_AUDIO, ENCODE));
	ui.audio_codec->setCurrentIndex(-1);
	audio_bitrate = num_chan = 0;
}

void 
ChooseAudioCodec::on_audio_codec_activated(const QString text)
{
	audio_codec = text;
//	emitParametersChanged();
}

void 
ChooseAudioCodec::on_audio_bitrate_valueChanged(int value)
{
	audio_bitrate = value;
//	emitParametersChanged();

}

QStringList
ChooseAudioCodec::getParams() const
{
	QStringList tmp;
	tmp << "-acodec"  << (audio_codec.isEmpty()?"copy":audio_codec)
	    << check_not_null(audio_bitrate, "-ab") 
	    << check_not_null(num_chan, "-ac") ;
	return tmp;
}


void 
ChooseAudioCodec::on_num_chan_valueChanged(int value)
{
	num_chan = value;
}

