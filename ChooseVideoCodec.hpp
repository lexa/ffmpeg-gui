#ifndef CHOOSE_VIDEO_CODEC_H_
#define CHOOSE_VIDEO_CODEC_H_

#include <QString>
#include <QWidget>
#include <QLabel>

#include "ui_ChooseVideoCodec.h"
#include "FFMPEG.hpp"


//виджет для выбора видео кодерка в который конвертить
class ChooseVideoCodec :
	public QWidget
{
	Q_OBJECT
public:
	ChooseVideoCodec (int, QWidget* parent = 0);
signals:
	void parametersChanged(int, QStringList);
private:
	void emitParametersChanged();

	QString codec;
	int bitrate, max_bitrate, min_bitrate;
	QString size;
	QString aspect;
	Ui::ChooseVideoCodec ui;
	int id;
	      
private slots:
	void on_video_codec_activated(const QString);
	void on_size_activated(const QString);
	void on_aspect_activated(const QString);
	void on_bitrate_valueChanged(int);
	void on_min_bitrate_valueChanged(int);
	void on_max_bitrate_valueChanged(int);
};
#endif
