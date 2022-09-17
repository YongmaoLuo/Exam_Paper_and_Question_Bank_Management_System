/********************************************************************************
** Form generated from reading UI file 'rulemakerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEMAKERDIALOG_H
#define UI_RULEMAKERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_RuleMakerDialog
{
public:
    QTextEdit *bulletinTextEdit;
    QPushButton *submitButton;
    QPushButton *exitButton;
    QListWidget *bulletinListWidget;
    QPushButton *deleteButton;
    QPushButton *createButton;

    void setupUi(QDialog *RuleMakerDialog)
    {
        if (RuleMakerDialog->objectName().isEmpty())
            RuleMakerDialog->setObjectName(QString::fromUtf8("RuleMakerDialog"));
        RuleMakerDialog->resize(715, 350);
        bulletinTextEdit = new QTextEdit(RuleMakerDialog);
        bulletinTextEdit->setObjectName(QString::fromUtf8("bulletinTextEdit"));
        bulletinTextEdit->setGeometry(QRect(390, 20, 291, 191));
        submitButton = new QPushButton(RuleMakerDialog);
        submitButton->setObjectName(QString::fromUtf8("submitButton"));
        submitButton->setGeometry(QRect(490, 230, 93, 28));
        exitButton = new QPushButton(RuleMakerDialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(310, 280, 93, 41));
        bulletinListWidget = new QListWidget(RuleMakerDialog);
        bulletinListWidget->setObjectName(QString::fromUtf8("bulletinListWidget"));
        bulletinListWidget->setGeometry(QRect(30, 20, 281, 192));
        deleteButton = new QPushButton(RuleMakerDialog);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(40, 230, 93, 28));
        createButton = new QPushButton(RuleMakerDialog);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setGeometry(QRect(180, 230, 93, 28));

        retranslateUi(RuleMakerDialog);

        QMetaObject::connectSlotsByName(RuleMakerDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleMakerDialog)
    {
        RuleMakerDialog->setWindowTitle(QCoreApplication::translate("RuleMakerDialog", "Dialog", nullptr));
        submitButton->setText(QCoreApplication::translate("RuleMakerDialog", "\346\217\220\344\272\244", nullptr));
        exitButton->setText(QCoreApplication::translate("RuleMakerDialog", "\351\200\200\345\207\272", nullptr));
        deleteButton->setText(QCoreApplication::translate("RuleMakerDialog", "\345\210\240\351\231\244", nullptr));
        createButton->setText(QCoreApplication::translate("RuleMakerDialog", "\345\210\233\345\273\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleMakerDialog: public Ui_RuleMakerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEMAKERDIALOG_H
