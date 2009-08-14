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

	// FileFormats  tmp;
	// qWarning() <<  tmp.getAvailableEncodeFileFormats();
	// FileInfo fileInfo;
	// fileInfo.setFilename("/home/lexa/tmp/ffmpeg/movie.avi");
		
	return app.exec();
}
