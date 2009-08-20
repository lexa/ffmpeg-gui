#ifndef CHOOSE_FILE_FORMAT_H_
#define CHOOSE_FILE_FORMAT_H_

#include <QString>
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>

#include "FFMPEG.hpp"
#include "Utils.hpp"

//виджет в котором можно выбрать тип контейнера в который конвертить
class ChooseFileFormat :
	public QWidget
{
	Q_OBJECT
public:
	ChooseFileFormat (int id, QWidget* parent = 0);
	QString getFormat();//возращает выбраный формат файла (опция -f)
//	~ChooseFileFormat() {};
signals:
	void parametersChanged(int, QString);
private:
	QString format;
	QString outFile;
	int id;
private slots:
	void setFormat(const QString);
	void setOutFile(QString );
	void collectLineOptions();
};

#endif
