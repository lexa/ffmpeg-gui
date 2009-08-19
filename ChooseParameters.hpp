#ifndef CHOOSE_PARAMETERS_H_
#define CHOOSE_PARAMETERS_H_

#include <QString>
#include <QWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>

#include "FFMPEG.hpp"

//TODO сделать нормальные деревья и всё на них переписать
//виджет в котором можно выбрать параметры кодеков и формата, этот класс просто чтоб от него наследовать виджеты которые реально что-то выбирают
// class GenericChooseFormat : public QWidget
// {
// public:
// 	virtual QString getFormat() =0;
// 	virtual ~GenericChooseFormat() {};
// };

//виджет в котором можно выбрать тип контейнера в который конвертить
class ChooseFileFormat :
	public QWidget
{
	Q_OBJECT
public:
	ChooseFileFormat (QWidget* parent = 0);
	QString getFormat();//возращает выбраный формат файла (опция -f)
//	~ChooseFileFormat() {};
signals:
	void parametersChanged(int, QString);
private:
	QString format;
private slots:
	void setFormat(const QString);
};

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

class EmptyChoose : public QWidget
{
	Q_OBJECT
public:
	EmptyChoose(QWidget* parent=0);
	virtual QString getFormat() {return QString("");};
	virtual ~EmptyChoose() {};
};


//виджет который содержит информацию о файле и элементы для управления кодеком/контэйнером 
//1 экземпляр виджета - 1 файл 
class ChooseParameters : 
	public QWidget
{
	Q_OBJECT
public:
	ChooseParameters(QString filename, QWidget *parent = 0);
signals:
	void parametersChanged (QString);//испускается когда строка для кодирования меняется

	// public slots:
	// 	 void setFilename(QString filename);
private slots:
//	void currentItemChanged (QTreeWidgetItem* current);//когда элемент из дерева выбирается
	void codecParametersChanged(int, QString);//собственно очерёдность потока и его параметры 
private:
 	QTreeWidget *tree;
	QSplitter* l;
	QList<QString> listParameters;
};

#endif //CHOOSE_PARAMETERS_H_
