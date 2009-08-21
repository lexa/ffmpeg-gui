/********************************************************************************
** Form generated from reading ui file 'ChooseFileFormat.ui'
**
** Created: Fri Aug 21 15:10:59 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CHOOSEFILEFORMAT_H
#define UI_CHOOSEFILEFORMAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseFileFormat
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton;

    void setupUi(QWidget *ChooseFileFormat)
    {
        if (ChooseFileFormat->objectName().isEmpty())
            ChooseFileFormat->setObjectName(QString::fromUtf8("ChooseFileFormat"));
        ChooseFileFormat->resize(401, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChooseFileFormat->sizePolicy().hasHeightForWidth());
        ChooseFileFormat->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(ChooseFileFormat);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ChooseFileFormat);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(ChooseFileFormat);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ChooseFileFormat);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox = new QComboBox(ChooseFileFormat);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(ChooseFileFormat);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        QWidget::setTabOrder(lineEdit, comboBox);
        QWidget::setTabOrder(comboBox, pushButton);

        retranslateUi(ChooseFileFormat);

        QMetaObject::connectSlotsByName(ChooseFileFormat);
    } // setupUi

    void retranslateUi(QWidget *ChooseFileFormat)
    {
        ChooseFileFormat->setWindowTitle(QApplication::translate("ChooseFileFormat", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ChooseFileFormat", "Output File", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ChooseFileFormat", "Output Container Format:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ChooseFileFormat", "Advanced(not implemenred)", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ChooseFileFormat);
    } // retranslateUi

};

namespace Ui {
    class ChooseFileFormat: public Ui_ChooseFileFormat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEFILEFORMAT_H
