/********************************************************************************
** Form generated from reading UI file 'admindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINDIALOG_H
#define UI_ADMINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminDialog
{
public:
    QListWidget *applicationlistWidget;
    QLabel *label;
    QListWidget *userListWidget;
    QLabel *label_2;
    QPushButton *deleteButton;
    QPushButton *exitButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *agreeButton;
    QPushButton *rejectButton;

    void setupUi(QDialog *AdminDialog)
    {
        if (AdminDialog->objectName().isEmpty())
            AdminDialog->setObjectName(QString::fromUtf8("AdminDialog"));
        AdminDialog->resize(827, 530);
        applicationlistWidget = new QListWidget(AdminDialog);
        applicationlistWidget->setObjectName(QString::fromUtf8("applicationlistWidget"));
        applicationlistWidget->setGeometry(QRect(480, 130, 256, 192));
        label = new QLabel(AdminDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(570, 80, 101, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(20);
        label->setFont(font);
        userListWidget = new QListWidget(AdminDialog);
        userListWidget->setObjectName(QString::fromUtf8("userListWidget"));
        userListWidget->setGeometry(QRect(81, 131, 256, 192));
        label_2 = new QLabel(AdminDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 80, 151, 31));
        label_2->setFont(font);
        deleteButton = new QPushButton(AdminDialog);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(160, 360, 93, 28));
        exitButton = new QPushButton(AdminDialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(360, 440, 111, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        exitButton->setFont(font1);
        layoutWidget = new QWidget(AdminDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(510, 360, 201, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        agreeButton = new QPushButton(layoutWidget);
        agreeButton->setObjectName(QString::fromUtf8("agreeButton"));
        agreeButton->setLayoutDirection(Qt::LeftToRight);
        agreeButton->setFlat(false);

        horizontalLayout->addWidget(agreeButton);

        rejectButton = new QPushButton(layoutWidget);
        rejectButton->setObjectName(QString::fromUtf8("rejectButton"));

        horizontalLayout->addWidget(rejectButton);


        retranslateUi(AdminDialog);

        agreeButton->setDefault(false);


        QMetaObject::connectSlotsByName(AdminDialog);
    } // setupUi

    void retranslateUi(QDialog *AdminDialog)
    {
        AdminDialog->setWindowTitle(QCoreApplication::translate("AdminDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AdminDialog", "\347\224\263\350\257\267", nullptr));
        label_2->setText(QCoreApplication::translate("AdminDialog", "\347\263\273\347\273\237\347\224\250\346\210\267", nullptr));
        deleteButton->setText(QCoreApplication::translate("AdminDialog", "\345\210\240\351\231\244", nullptr));
        exitButton->setText(QCoreApplication::translate("AdminDialog", "\351\200\200\345\207\272", nullptr));
        agreeButton->setText(QCoreApplication::translate("AdminDialog", "\345\220\214\346\204\217", nullptr));
        rejectButton->setText(QCoreApplication::translate("AdminDialog", "\346\213\222\347\273\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminDialog: public Ui_AdminDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINDIALOG_H
