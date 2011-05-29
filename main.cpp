#include <QApplication>


#include "MainWindow.hpp"
#include "FileList.hpp"

#include "FFMPEG.hpp"


class test_class 
{
public:
	GUI::FileList *treeWidget;
};
	


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	GUI::MainWindow* window = new GUI::MainWindow();
	window->show();

	return app.exec();
}

