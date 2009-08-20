#include "ChooseFileFormat.hpp"



ChooseFileFormat::ChooseFileFormat (int id, QWidget* parent)
	:QWidget (parent)
{
	QComboBox* combobox = new QComboBox;
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(combobox);
	QStringList availFormats = getAvailableEncodeFileFormats();
	combobox->addItems(availFormats);
	QObject::connect(combobox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(setFormat(const QString)));
	setFormat(availFormats[0]);
	setOutFile("/tmp/ffmpeg-gui.tmp");

	this->id = id;
	QWidget* output_file = new SelectionFile(tr("Output File:"));
	layout->addWidget(output_file);
	QObject::connect(output_file, SIGNAL(fileChanged(QString)), this, SLOT(setOutFile(QString)));

	setLayout(layout);
}

// QString
// ChooseFileFormat::getFormat()
// {
// 	return format;
// }

void
ChooseFileFormat::setFormat(const QString text)
{
	format = text;
	collectLineOptions();
}

void
ChooseFileFormat::setOutFile(QString text)
{
 	outFile = text;
	collectLineOptions();
}
void
ChooseFileFormat::collectLineOptions()
{
//	qWarning() << (QString("-f ") + format + "  " + outFile);
	emit parametersChanged(id, (QString("-f ") + format + "  " + outFile));
}
