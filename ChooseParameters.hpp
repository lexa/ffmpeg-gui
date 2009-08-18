#ifndef CODEC_SELECTION_H_
#define CODEC_SELECTION_H_

#include <QString>
#include <QWidget>
#include <QTreeWidget>
#include <QVBoxLayout>


#include "FFMPEG.hpp"


class ShowFileInfo : 
	public QWidget
{
	Q_OBJECT
public:
	ShowFileInfo(QWidget* parent = 0);
public slots:
	void setFilename(QString);
private:
	QTreeWidget *tree;
};

//TODO сделать нормальные деревья и всё на них переписать
//виджет в котором можно выбрать параметры кодеков и формата, этот класс просто чтоб от него наследовать виджеты которые реально что-то выбирают
class GenericChooseFormat 
{
public:
	virtual QString getFormat() =0;
	virtual ~GenericChooseFormat() {};
};

//виджет в котором можно выбрать тип контейнера в который конвертить
class ChooseFileFormat :
	public QWidget, public GenericChooseFormat
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
class ChooseParameters : 
	public QWidget
{
	Q_OBJECT
public:
	ChooseParameters(QWidget *parent = 0);
	QString getSelectedParameters ();//аозвращает строку для ffmpeg для конвертирования 
private:
	
}

#endif //CODEC_SELECTION_H_
