/********************************************************************************
** Form generated from reading UI file 'admindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINDIALOG_H
#define UI_ADMINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            AdminDialog->setObjectName(QStringLiteral("AdminDialog"));
        AdminDialog->resize(827, 530);
        applicationlistWidget = new QListWidget(AdminDialog);
        applicationlistWidget->setObjectName(QStringLiteral("applicationlistWidget"));
        applicationlistWidget->setGeometry(QRect(480, 130, 256, 192));
        label = new QLabel(AdminDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(570, 80, 101, 31));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(20);
        label->setFont(font);
        userListWidget = new QListWidget(AdminDialog);
        userListWidget->setObjectName(QStringLiteral("userListWidget"));
        userListWidget->setGeometry(QRect(81, 131, 256, 192));
        label_2 = new QLabel(AdminDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 80, 151, 31));
        label_2->setFont(font);
        deleteButton = new QPushButton(AdminDialog);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setGeometry(QRect(160, 360, 93, 28));
        exitButton = new QPushButton(AdminDialog);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(360, 440, 111, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(12);
        exitButton->setFont(font1);
        layoutWidget = new QWidget(AdminDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(510, 360, 201, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        agreeButton = new QPushButton(layoutWidget);
        agreeButton->setObjectName(QStringLiteral("agreeButton"));
        agreeButton->setLayoutDirection(Qt::LeftToRight);
        agreeButton->setFlat(false);

        horizontalLayout->addWidget(agreeButton);

        rejectButton = new QPushButton(layoutWidget);
        rejectButton->setObjectName(QStringLiteral("rejectButton"));

        horizontalLayout->addWidget(rejectButton);


        retranslateUi(AdminDialog);

        agreeButton->setDefault(false);


        QMetaObject::connectSlotsByName(AdminDialog);
    } // setupUi

    void retranslateUi(QDialog *AdminDialog)
    {
        AdminDialog->setWindowTitle(QApplication::translate("AdminDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("AdminDialog", "\347\224\263\350\257\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("AdminDialog", "\347\263\273\347\273\237\347\224\250\346\210\267", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("AdminDialog", "\345\210\240\351\231\244", Q_NULLPTR));
        exitButton->setText(QApplication::translate("AdminDialog", "\351\200\200\345\207\272", Q_NULLPTR));
        agreeButton->setText(QApplication::translate("AdminDialog", "\345\220\214\346\204\217", Q_NULLPTR));
        rejectButton->setText(QApplication::translate("AdminDialog", "\346\213\222\347\273\235", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AdminDialog: public Ui_AdminDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINDIALOG_H
