#include "ChooseFileFormat.hpp"

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
