/********************************************************************************
** Form generated from reading UI file 'signupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPDIALOG_H
#define UI_SIGNUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUpDialog
{
public:
    QLabel *label_4;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *userName;
    QLineEdit *password;
    QLineEdit *identity;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *prompt;

    void setupUi(QDialog *SignUpDialog)
    {
        if (SignUpDialog->objectName().isEmpty())
            SignUpDialog->setObjectName(QString::fromUtf8("SignUpDialog"));
        SignUpDialog->resize(409, 316);
        label_4 = new QLabel(SignUpDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(51, 71, 166, 32));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(16);
        label_4->setFont(font);
        confirmButton = new QPushButton(SignUpDialog);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        confirmButton->setGeometry(QRect(91, 230, 93, 28));
        cancelButton = new QPushButton(SignUpDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(190, 230, 93, 28));
        layoutWidget = new QWidget(SignUpDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 110, 173, 81));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        userName = new QLineEdit(layoutWidget);
        userName->setObjectName(QString::fromUtf8("userName"));

        verticalLayout->addWidget(userName);

        password = new QLineEdit(layoutWidget);
        password->setObjectName(QString::fromUtf8("password"));

        verticalLayout->addWidget(password);

        identity = new QLineEdit(layoutWidget);
        identity->setObjectName(QString::fromUtf8("identity"));

        verticalLayout->addWidget(identity);

        layoutWidget1 = new QWidget(SignUpDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 110, 107, 81));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(9);
        label->setFont(font1);
        label->setIndent(0);

        verticalLayout_2->addWidget(label);

        prompt = new QLabel(SignUpDialog);
        prompt->setObjectName(QString::fromUtf8("prompt"));
        prompt->setGeometry(QRect(111, 200, 151, 20));

        retranslateUi(SignUpDialog);

        QMetaObject::connectSlotsByName(SignUpDialog);
    } // setupUi

    void retranslateUi(QDialog *SignUpDialog)
    {
        SignUpDialog->setWindowTitle(QCoreApplication::translate("SignUpDialog", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("SignUpDialog", "              \346\263\250\345\206\214", nullptr));
        confirmButton->setText(QCoreApplication::translate("SignUpDialog", "\347\241\256\350\256\244", nullptr));
        cancelButton->setText(QCoreApplication::translate("SignUpDialog", "\345\217\226\346\266\210", nullptr));
        label_2->setText(QCoreApplication::translate("SignUpDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_3->setText(QCoreApplication::translate("SignUpDialog", "\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("SignUpDialog", "\345\234\250\347\263\273\347\273\237\344\270\255\347\232\204\350\272\253\344\273\275", nullptr));
        prompt->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignUpDialog: public Ui_SignUpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPDIALOG_H
