#ifndef CHOOSE_FILE_FORMAT_H_
#define CHOOSE_FILE_FORMAT_H_

#include <QString>
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QStringList>

#include "FFMPEG.hpp"
#include "Utils.hpp"
#include "ChooseGeneric.hpp"
#include "ui_ChooseFileFormat.h"

//виджет в котором можно выбрать тип контейнера в который конвертить
// class ChooseFileFormat :
// 	public QWidget
// {
// 	Q_OBJECT
// public:
// 	ChooseFileFormat (int id, QWidget* parent = 0);
// //	QString getFormat();//возращает выбраный формат файла (опция -f)
// //	~ChooseFileFormat() {};
// signals:
// 	void parametersChanged(int, QString);
// private:
// 	QString format;
// 	QString outFile;
// 	int id;
// private slots:
// 	void setFormat(const QString);
// 	void setOutFile(QString );
// 	void collectLineOptions();
// };

class ChooseFileFormat :
	public GenericChoose  
{
	Q_OBJECT
public:
	ChooseFileFormat (QWidget* parent = 0);
	virtual QStringList getParams() const;
signals:
	void parametersChanged(int, QStringList);
private slots:
	void on_lineEdit_textEdited(QString);
	void on_comboBox_activated (const QString);
private:
	void emitParametersChanged();
	QString outFile;
	QStringList format;
//	int id;
	Ui::ChooseFileFormat ui;
};

#endif
