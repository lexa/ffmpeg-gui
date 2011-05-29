#include "MainWindow.hpp"

namespace GUI {

	MainWindow::MainWindow (QWidget *parent)
		:QMainWindow(parent)
	{
		ui.setupUi(this);

		setWindowTitle(tr("ffmpeg-gui"));

//	setAcceptDrops(true);//разрешили перетаскивать
	}



}
