#ifndef CHOOSE_VIDEO_CODEC_H_
#define CHOOSE_VIDEO_CODEC_H_

#include <QString>
#include <QWidget>
#include <QLabel>

#include "FFMPEG.hpp"


//виджет для выбора видео кодерка в который конвертить
class ChooseVideoCodec :
	public QWidget
{
	Q_OBJECT
public:
	ChooseVideoCodec (QWidget* parent = 0);
//	virtual QString getFormat();//возращает выбране св-ва кодека (по умолчанию copy)
	virtual ~ChooseVideoCodec() {};
signals:
	void parametersChanged(int, QString);
private:
	QString format;
private slots:
	void setFormat(const QString);
};
#endif
