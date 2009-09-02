#ifndef CHOOSE_PARAMETERS_H_
#define CHOOSE_PARAMETERS_H_

#include <QString>
#include <QWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QMap>
#include <QList>
#include <QUrl>

#include "FFMPEG.hpp"

#include "ChooseGeneric.hpp"
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



class EmptyChoose : public GenericChoose
{
	Q_OBJECT
public:
	EmptyChoose(QWidget* parent=0);
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
	ChooseParameters(QWidget *parent = 0);
public slots:
	void addUrl(QUrl);
	void clear();
	QStringList getParams();
private:
	int filenum;
 	QTreeWidget *tree;
//	QSplitter* l;
	QList<QUrl> filenames;
	QList <GenericChoose* > built_widgets;
	ChooseFileFormat* container_tab;
	QTabWidget* selectors;
	QMap<CodecType, int> cnt_streams;//кол-во стримов каждого типа
};

#endif //CHOOSE_PARAMETERS_H_
