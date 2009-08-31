#ifndef UTILS_H_
#define UTILS_H_

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QUrl>
#include <QList>

class SelectionFile 
	: public QWidget
{
	Q_OBJECT
public:
 	SelectionFile (QString label, QWidget* parent = 0);
public slots:
	void fileDropped(QList<QUrl> files_url);
private slots:
	void showFileDialog();
private:
	QLineEdit* inputFilename;
	QString label;
signals:
	void fileChanged(QList<QUrl> );
};

QHBoxLayout* AddLabel(QWidget* w, QString label="without label");

QStringList check_not_null (int x, QString key);

QString num_to_string(int n);

#endif
