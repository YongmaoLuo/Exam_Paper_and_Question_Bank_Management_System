/********************************************************************************
** Form generated from reading UI file 'rulemakerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEMAKERDIALOG_H
#define UI_RULEMAKERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
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
            RuleMakerDialog->setObjectName(QStringLiteral("RuleMakerDialog"));
        RuleMakerDialog->resize(715, 350);
        bulletinTextEdit = new QTextEdit(RuleMakerDialog);
        bulletinTextEdit->setObjectName(QStringLiteral("bulletinTextEdit"));
        bulletinTextEdit->setGeometry(QRect(390, 20, 291, 191));
        submitButton = new QPushButton(RuleMakerDialog);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setGeometry(QRect(490, 230, 93, 28));
        exitButton = new QPushButton(RuleMakerDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(310, 280, 93, 41));
        bulletinListWidget = new QListWidget(RuleMakerDialog);
        bulletinListWidget->setObjectName(QStringLiteral("bulletinListWidget"));
        bulletinListWidget->setGeometry(QRect(30, 20, 281, 192));
        deleteButton = new QPushButton(RuleMakerDialog);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setGeometry(QRect(40, 230, 93, 28));
        createButton = new QPushButton(RuleMakerDialog);
        createButton->setObjectName(QStringLiteral("createButton"));
        createButton->setGeometry(QRect(180, 230, 93, 28));

        retranslateUi(RuleMakerDialog);

        QMetaObject::connectSlotsByName(RuleMakerDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleMakerDialog)
    {
        RuleMakerDialog->setWindowTitle(QApplication::translate("RuleMakerDialog", "Dialog", Q_NULLPTR));
        submitButton->setText(QApplication::translate("RuleMakerDialog", "\346\217\220\344\272\244", Q_NULLPTR));
        exitButton->setText(QApplication::translate("RuleMakerDialog", "\351\200\200\345\207\272", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("RuleMakerDialog", "\345\210\240\351\231\244", Q_NULLPTR));
        createButton->setText(QApplication::translate("RuleMakerDialog", "\345\210\233\345\273\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RuleMakerDialog: public Ui_RuleMakerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEMAKERDIALOG_H
