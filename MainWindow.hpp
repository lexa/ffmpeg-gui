#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QtDebug>
#include <QString>
#include <QProcess>
#include <QMessageBox>
#include <QByteArrayMatcher>
#include <QTreeWidget>
#include <QTreeWidgetItem>



extern "C" {
#include <libavformat/avformat.h>
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
#include <libavcodec/opt.h>
#include <libavutil/fifo.h>
#include <libavutil/avstring.h>
}

#include "FFMPEG.hpp"
#include "ChooseParameters.hpp"

#include "Utils.hpp"

class MainWindow 
	: public QWidget
{
	Q_OBJECT
	
public:
	MainWindow (QWidget *parent = 0);
	virtual ~MainWindow () {};

private:
//	SelectionFile* inputFile;
//	SelectionFile* outputFile;
	QVBoxLayout *layoutMain;
	ChooseParameters *params;
private slots:
	void inputFileChanged(QString filename);
//	void outputFileChanged(QString filename);
};

#endif //MAIN_WINDOW_H_
