#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>
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
#include "CodecSelection.hpp"
class SelectionInputFile : public QWidget
{
	Q_OBJECT
	
public:
 	SelectionInputFile (QWidget *parent = 0);
					 
private slots:
	void showChooseInputFileDialog();
	void emitInputFileChanged ();
private:
	QLineEdit* inputFilename;
signals:
	void inputFileChanged(QString);
};


class MainWindow : public QWidget
{
	Q_OBJECT
	
public:
	MainWindow (QWidget *parent = 0);
	virtual ~MainWindow () {};

private:
	SelectionInputFile* inputFileName;

};
