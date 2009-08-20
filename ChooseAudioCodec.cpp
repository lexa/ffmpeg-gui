#include "ChooseAudioCodec.hpp"

ChooseAudioCodec::ChooseAudioCodec (QWidget* parent)
	:QWidget(parent), format("copy")
{
	QComboBox* list = new QComboBox;
	Codecs availCodecs ;
	list->addItems(availCodecs.getAvailableCodecs(CODEC_TYPE_AUDIO, ENCODE));
	QVBoxLayout* l = new QVBoxLayout;
	QHBoxLayout* tmp = new QHBoxLayout;
	
	tmp->addWidget(new QLabel(tr("Audio Codec:")));
	tmp->addWidget(list);
	
	l->addItem(tmp);
	setLayout(l);
	QObject::connect(list, SIGNAL(activated(const QString)), this, SLOT(setFormat(const QString))); 
}


void 
ChooseAudioCodec::setFormat(const QString new_format)
{
	format=new_format;
}
