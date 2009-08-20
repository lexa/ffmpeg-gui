#ifndef UTILS_H_
#define UTILS_H_

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class SelectionFile 
	: public QWidget
{
	Q_OBJECT
public:
 	SelectionFile (QString label, QWidget* parent = 0);
private slots:
	void showFileDialog();
	void emitFileChanged ();
private:
	QLineEdit* inputFilename;
	QString label;
signals:
	void fileChanged(QString);
};

QHBoxLayout* AddLabel(QWidget* w, QString label="without label");

#endif
