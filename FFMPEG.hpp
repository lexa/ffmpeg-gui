#ifndef FFMPEG_MY_H
#define FFMPEG_MY_H

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


#include <QWidget>
#include <QObject>
#include <QStringList>
#include <QList>
#include <QtGlobal> 
#include <QtGlobal>
#include <QtDebug>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QComboBox>

#include <iostream>


//TODO класс singleton который будет держать ffmpeg проинициализированным
//singleton держащий ffmpeg инициализированным
class LibAVC {
public:
	static LibAVC* instance ();
private:
	static LibAVC* uniqueInstance;
protected:
	LibAVC();
	LibAVC(LibAVC*);
	LibAVC* operator=(LibAVC*);
	~LibAVC();
	
};


class FileFormats : public QObject
{
	Q_OBJECT
public:
	FileFormats(QObject* parent = 0);
	QStringList getAvailableDecodeFileFormats() const;
	QStringList getAvailableEncodeFileFormats() const;
private:
	// typedef struct {
	// 	bool decode, encode : 1;
	// 	QString name, long_name;
	// } FileFormatsT;
	
	QStringList encodeFileFormats;
	QStringList decodeFileFormats;
};

enum Appointment {DECODE=1, ENCODE=2};
class Codecs : public QObject
{
	Q_OBJECT
	
public:
	Codecs(QObject* parent = 0);
//	enum CodecType {CODEC_TYPE_SUBTITLE CODEC_TYPE_VIDEO CODEC_TYPE_AUDIO}
	QStringList getAvailableCodecs(CodecType type, int coder /* Appointment*/) const;
private:
	struct CodecT {
		CodecType type;
		int coder;//Appointment
		QString name;
	};
	mutable QList <CodecT> allCodecs;
};

//виджет отображающий информацию о файле
class FileInfo : 
	public QWidget
{
	Q_OBJECT
public:
	FileInfo(QWidget* parent = 0);
public slots:
	void setFilename(QString);
private:
	QTreeWidget *tree;
};

//виджет в котором можно выбрать параметры кодеков и формата, этот класс просто чтоб от него наследовать виджеты которые реально что-то выбирают
class GenericChooseFormat 
{
public:
//	GenericChooseFormat ();
	virtual QString getFormat() =0;
	virtual ~GenericChooseFormat() ;
};

//виджет в котором можно выбрать тип контейнера в который конвертить
class ChooseFileFormat :
	public QWidget
{
	Q_OBJECT
public:
	ChooseFileFormat (QWidget* parent = 0);
	virtual QString getFormat();//возращает выбраный формат файла (опция -f)
	virtual ~ChooseFileFormat() {};
private:
	QString format;
private slots:
	void setFormat(const QString);
};

//виджет который содержит элементы для управления кодеком/контэйнером
//определять виджет по его типу
// class ChooseParameters : 
// 	public QWidget
// {
// 	Q_OBJECT

// }

#endif //FFMPEG_MY_H
