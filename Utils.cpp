#include "Utils.hpp"

void
SelectionFile::showFileDialog()
{
//	std::cerr << "file dialog" << std::endl;
	QString filename = QFileDialog::getOpenFileName(this, label);
//	qWarning() << filename ;

	inputFilename->setText(filename);
//	std::cerr << "end" << std::endl;
}


void 
SelectionFile::emitFileChanged ()
{
	emit fileChanged(inputFilename->text());
}

SelectionFile::SelectionFile (QString label, QWidget* parent)
	:QWidget(parent)
{
	QLabel *inputLabel = new QLabel(label);
	this->label = label;
	
	inputFilename = new QLineEdit;
	QPushButton* selectFile = new QPushButton(tr("Select File"));

	QHBoxLayout *layoutFile = new QHBoxLayout;
	layoutFile->addWidget (inputLabel);
	layoutFile->addWidget (inputFilename);
	layoutFile->addWidget (selectFile);

	QObject::connect (selectFile, SIGNAL(clicked()), this, SLOT(showFileDialog()));
	QObject::connect (inputFilename, SIGNAL(textChanged(QString)), this, SLOT(emitFileChanged()) );
	QVBoxLayout *layoutMain = new QVBoxLayout;
	layoutMain->addLayout(layoutFile);
	setLayout(layoutMain);
}

QHBoxLayout*
AddLabel(QWidget* w, QString label)
{
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(new QLabel(label));
	layout->addWidget(w);
	return layout;
}

QStringList
check_not_null (int x, QString key)
{
	QString str;
	str.setNum(x, 10);
	QStringList rez;
	rez << ((x!=0)?key:"")  << ((x!=0)?str:"") ;
	return rez;
}
