#ifndef CHOOSE_AUDIO_CODEC_H_
#define CHOOSE_AUDIO_CODEC_H_

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QComboBox>

#include "FFMPEG.hpp"
#include "Utils.hpp"
#include "ChooseGeneric.hpp"
#include "ui_ChooseAudioCodec.h"

class ChooseAudioCodec :
	public GenericChoose
{
	Q_OBJECT
public:
	ChooseAudioCodec (QWidget* parent = 0);
signals:
	void parametersChanged(int, QStringList);
private:
	QString format;
	Ui::ChooseAudioCodec ui;
	int num_chan, audio_bitrate;
	QString audio_codec;
//	void emitParametersChanged();
	QStringList getParams() const;
private slots:
	void on_audio_codec_activated(const QString);
	void on_audio_bitrate_valueChanged(int);
	void on_num_chan_valueChanged(int);
};
#endif  //CHOOSE_AUDIO_CODEC_H_
