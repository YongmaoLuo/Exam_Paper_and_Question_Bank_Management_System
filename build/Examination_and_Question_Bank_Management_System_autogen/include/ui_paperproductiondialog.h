/********************************************************************************
** Form generated from reading UI file 'paperproductiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAPERPRODUCTIONDIALOG_H
#define UI_PAPERPRODUCTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PaperProductionDialog
{
public:
    QListWidget *listWidget;
    QPushButton *deleteButton;
    QPushButton *outputButton;
    QPushButton *hideButton;

    void setupUi(QDialog *PaperProductionDialog)
    {
        if (PaperProductionDialog->objectName().isEmpty())
            PaperProductionDialog->setObjectName(QString::fromUtf8("PaperProductionDialog"));
        PaperProductionDialog->resize(571, 341);
        listWidget = new QListWidget(PaperProductionDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(45, 30, 471, 192));
        deleteButton = new QPushButton(PaperProductionDialog);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(120, 240, 93, 28));
        outputButton = new QPushButton(PaperProductionDialog);
        outputButton->setObjectName(QString::fromUtf8("outputButton"));
        outputButton->setGeometry(QRect(340, 240, 93, 28));
        hideButton = new QPushButton(PaperProductionDialog);
        hideButton->setObjectName(QString::fromUtf8("hideButton"));
        hideButton->setGeometry(QRect(230, 290, 93, 28));

        retranslateUi(PaperProductionDialog);

        QMetaObject::connectSlotsByName(PaperProductionDialog);
    } // setupUi

    void retranslateUi(QDialog *PaperProductionDialog)
    {
        PaperProductionDialog->setWindowTitle(QCoreApplication::translate("PaperProductionDialog", "Dialog", nullptr));
        deleteButton->setText(QCoreApplication::translate("PaperProductionDialog", "\345\210\240\351\231\244", nullptr));
        outputButton->setText(QCoreApplication::translate("PaperProductionDialog", "\350\276\223\345\207\272\350\257\225\345\215\267", nullptr));
        hideButton->setText(QCoreApplication::translate("PaperProductionDialog", "\351\232\220\350\227\217\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaperProductionDialog: public Ui_PaperProductionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAPERPRODUCTIONDIALOG_H
