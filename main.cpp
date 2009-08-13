#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include "MainWindow.hpp"
#include "FFMPEG.hpp"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow* window = new MainWindow();
	window->show();

	new FileFormats	;
	return app.exec();
}
