#ifndef CHOOSE_PARAMETERS_H_
#define CHOOSE_PARAMETERS_H_

#include <QString>
#include <QWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>


#include "FFMPEG.hpp"

//возвражать тип кодека и номер дорожки
// class ShowFileInfo : 
// 	public QWidget
// {
// 	Q_OBJECT
// public:
// 	ShowFileInfo(QWidget* parent = 0);
// private slots:
// 	void emitCurrentItemChanged(QTreeWidgetItem* current);
// public slots:
// 	void setFilename(QString);
// private:
// 	QTreeWidget *tree;
// 	QList<QPair<CodecType, QString> > info;

// signals:
// 	void currentItemChanged(CodecType type, int id);//испускается когда меняться выбор в списке кодеков
// };

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
private:
	QString format;
private slots:
	void setFormat(const QString);
};

//виджет для выбора кодерка в который конвертить
class ChooseCodec :
	public QWidget
{
	Q_OBJECT
public:
	ChooseCodec (CodecType codec, QWidget* parent = 0);
//	virtual QString getFormat();//возращает выбране св-ва кодека (по умолчанию copy)
	virtual ~ChooseCodec() {};
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
class ChooseParameters : 
	public QWidget
{
	Q_OBJECT
public:
	ChooseParameters(QWidget *parent = 0);
signals:
	void parametersChanged (QString);//испускается когда строка для кодирования меняется

public slots:
	void setFilename(QString filename);
private slots:
	void currentItemChanged (QTreeWidgetItem* current);//когда элемент из дерева выбирается
	void codecParametersChanged(QString);
private:
 	QTreeWidget *tree;
	QVBoxLayout* l;
	QWidget* currentChoose;
	QList <QWidget *> codecOptions;
};

#endif //CHOOSE_PARAMETERS_H_
