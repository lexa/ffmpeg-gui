#include "Utils.hpp"

void
SelectionFile::showFileDialog()
{
//	std::cerr << "file dialog" << std::endl;
	QStringList files = QFileDialog::getOpenFileNames(this, label);
	
	QList<QUrl> filenames;

	QStringList::Iterator it = files.begin();
	while(it != files.end()) {
		filenames.append(QUrl(*it));
		++it;
	}

	inputFilename->setText(files.join(","));
	emit fileChanged(filenames);
}


void
SelectionFile::fileDropped(QList<QUrl> urls)
{
	QString text;
	foreach (QUrl url, urls)
		text.append(url.toString());
		
	inputFilename->setText(text);
	emit fileChanged(urls);
}

// void 
// SelectionFile::emitFileChanged ()
// {
// 	emit fileChanged(inputFilename->text());
// }

SelectionFile::SelectionFile (QString label, QWidget* parent)
	:QWidget(parent)
{
	QLabel *inputLabel = new QLabel(label);
	this->label = label;
	
	inputFilename = new QLineEdit;
	inputFilename->setReadOnly(true);
	QPushButton* selectFile = new QPushButton(tr("Select File"));

	QHBoxLayout *layoutFile = new QHBoxLayout;
	layoutFile->addWidget (inputLabel);
	layoutFile->addWidget (inputFilename);
	layoutFile->addWidget (selectFile);

	QObject::connect (selectFile, SIGNAL(clicked()), this, SLOT(showFileDialog()));
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

QString num_to_string(int n)
{
	QString str;
	str.setNum(n);
	return str;
}
