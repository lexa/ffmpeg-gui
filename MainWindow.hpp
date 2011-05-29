#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_


#include <QWidget>
#include <QLineEdit>
#include <QtDebug>
#include <QString>
#include <QProcess>
#include <QMessageBox>
#include <QByteArrayMatcher>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSplitter>
#include <QDropEvent>


#include "Utils.hpp"

#include "ui_MainWindow.h"

namespace GUI {

	class MainWindow 
		: public QMainWindow
	{
		Q_OBJECT
	
		public:
		MainWindow (QWidget *parent = 0);
		virtual ~MainWindow () {};
				 
// public slots:
// 	void is_converting(void);
	private:
		Ui::MainWindow ui ;
//	void dropEvent(QDropEvent *event);
//	void dragEnterEvent(QDragEnterEvent *event);
// private slots:
// 	void inputFileChanged(QList<QUrl> filename);
	};

}

#endif //MAIN_WINDOW_H_
