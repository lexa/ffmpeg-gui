#ifndef CHOOSE_VIDEO_CODEC_H_
#define CHOOSE_VIDEO_CODEC_H_

#include <QString>
#include <QWidget>
#include <QLabel>

#include "FFMPEG.hpp"
#include "Utils.hpp"
#include "ChooseGeneric.hpp"
#include "ui_ChooseVideoCodec.h"

//виджет для выбора видео кодерка в который конвертить
class ChooseVideoCodec :
	public GenericChoose
{
	Q_OBJECT
public:
	ChooseVideoCodec (QWidget* parent = 0);
//signals:
//	void parametersChanged(int, QStringList);
	QStringList getParams() const;
private:
	void emitParametersChanged();

	QString codec;
	int bitrate, max_bitrate, min_bitrate;
	QString size;
	QString aspect;
	Ui::ChooseVideoCodec ui;
private slots:
	void on_video_codec_activated(const QString);
	void on_size_activated(const QString);
	void on_aspect_activated(const QString);
	void on_bitrate_valueChanged(int);
	void on_min_bitrate_valueChanged(int);
	void on_max_bitrate_valueChanged(int);
};
#endif
