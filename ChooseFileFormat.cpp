#include "ChooseFileFormat.hpp"



// ChooseFileFormat::ChooseFileFormat (int id, QWidget* parent)
// 	:QWidget (parent)
// {
// 	QComboBox* combobox = new QComboBox;
// 	QVBoxLayout *layout = new QVBoxLayout;
// 	layout->addWidget(combobox);
// 	QStringList availFormats = getAvailableEncodeFileFormats();
// 	combobox->addItems(availFormats);
// 	QObject::connect(combobox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(setFormat(const QString)));
// 	setFormat(availFormats[0]);
// 	setOutFile("/tmp/ffmpeg-gui.tmp");

// 	this->id = id;
// 	QWidget* output_file = new SelectionFile(tr("Output File:"));
// 	layout->addWidget(output_file);
// 	QObject::connect(output_file, SIGNAL(fileChanged(QString)), this, SLOT(setOutFile(QString)));

// 	setLayout(layout);
// }

// // QString
// // ChooseFileFormat::getFormat()
// // {
// // 	return format;
// // }

void
ChooseFileFormat::on_comboBox_activated(const QString text)
{
	format = QStringList(QString("-f")) << text;
}

void
ChooseFileFormat::on_lineEdit_textEdited(QString text)
{
	//set out file
 	outFile = text;
}


QStringList
ChooseFileFormat::getParams() const
{
	return QStringList(format) << ((ui.rewrite->checkState() == Qt::Checked)?"-y":"") << outFile ;
}

ChooseFileFormat::ChooseFileFormat (QWidget* parent)
 	:GenericChoose (parent)
{
	ui.setupUi(this);
 	QStringList availFormats = getAvailableEncodeFileFormats();
	ui.comboBox->addItems(availFormats);
}
