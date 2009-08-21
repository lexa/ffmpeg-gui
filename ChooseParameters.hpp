#ifndef CHOOSE_PARAMETERS_H_
#define CHOOSE_PARAMETERS_H_

#include <QString>
#include <QWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QHash>

#include "FFMPEG.hpp"

#include "ChooseAudioCodec.hpp"
#include "ChooseFileFormat.hpp"
#include "ChooseVideoCodec.hpp"


//TODO сделать нормальные деревья и всё на них переписать
//виджет в котором можно выбрать параметры кодеков и формата, этот класс просто чтоб от него наследовать виджеты которые реально что-то выбирают
// class GenericChooseFormat : public QWidget
// {
// public:
// 	virtual QString getFormat() =0;
// 	virtual ~GenericChooseFormat() {};
// };



class EmptyChoose : public QLabel
{
	Q_OBJECT
public:
	EmptyChoose(int id, QWidget* parent=0);
	~EmptyChoose() {};
signals:
	void parametersChanged(int, QString);

};


//виджет который содержит информацию о файле и элементы для управления кодеком/контэйнером 
//1 экземпляр виджета - 1 файл 
class ChooseParameters : 
	public QSplitter
{
	Q_OBJECT
public:
	ChooseParameters(QString filename, QWidget *parent = 0);
signals:
	void parametersChanged (QStringList);//испускается когда строка для кодирования меняется

	// public slots:
	// 	 void setFilename(QString filename);
private slots:
//	void currentItemChanged (QTreeWidgetItem* current);//когда элемент из дерева выбирается
	void codecParametersChanged(int, QStringList);//собственно очерёдность потока и его параметры 
private:
 	QTreeWidget *tree;
	QSplitter* l;
	QList<QStringList> listParameters;
	QString filename;
};

#endif //CHOOSE_PARAMETERS_H_
