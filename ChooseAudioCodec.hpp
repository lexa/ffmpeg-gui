#ifndef CHOOSE_AUDIO_CODEC_H_
#define CHOOSE_AUDIO_CODEC_H_

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QComboBox>

#include "FFMPEG.hpp"

class ChooseAudioCodec :
	public QWidget
{
	Q_OBJECT
public:
	ChooseAudioCodec (QWidget* parent = 0);
//	virtual QString getFormat();//возращает выбране св-ва кодека (по умолчанию copy)
	virtual ~ChooseAudioCodec() {};
signals:
	void parametersChanged(int, QString);
private:
	QString format;
private slots:
	void setFormat(const QString);
};
#endif
