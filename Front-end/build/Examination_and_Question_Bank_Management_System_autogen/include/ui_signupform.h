/********************************************************************************
** Form generated from reading UI file 'signupform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPFORM_H
#define UI_SIGNUPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUpForm
{
public:
    QPushButton *cancelButton;
    QPushButton *confirmButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *userName;
    QLineEdit *password;
    QLineEdit *identity;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *prompt;
    QLabel *label_4;

    void setupUi(QWidget *SignUpForm)
    {
        if (SignUpForm->objectName().isEmpty())
            SignUpForm->setObjectName(QString::fromUtf8("SignUpForm"));
        SignUpForm->resize(400, 300);
        cancelButton = new QPushButton(SignUpForm);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(189, 209, 93, 28));
        confirmButton = new QPushButton(SignUpForm);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        confirmButton->setGeometry(QRect(90, 209, 93, 28));
        layoutWidget = new QWidget(SignUpForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(159, 89, 173, 81));
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

        layoutWidget_2 = new QWidget(SignUpForm);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(39, 89, 107, 81));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label = new QLabel(layoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        label->setFont(font);
        label->setIndent(0);

        verticalLayout_2->addWidget(label);

        prompt = new QLabel(SignUpForm);
        prompt->setObjectName(QString::fromUtf8("prompt"));
        prompt->setGeometry(QRect(110, 179, 151, 20));
        label_4 = new QLabel(SignUpForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 50, 166, 32));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(16);
        label_4->setFont(font1);

        retranslateUi(SignUpForm);

        QMetaObject::connectSlotsByName(SignUpForm);
    } // setupUi

    void retranslateUi(QWidget *SignUpForm)
    {
        SignUpForm->setWindowTitle(QCoreApplication::translate("SignUpForm", "Form", nullptr));
        cancelButton->setText(QCoreApplication::translate("SignUpForm", "\345\217\226\346\266\210", nullptr));
        confirmButton->setText(QCoreApplication::translate("SignUpForm", "\347\241\256\350\256\244", nullptr));
        label_2->setText(QCoreApplication::translate("SignUpForm", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_3->setText(QCoreApplication::translate("SignUpForm", "\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("SignUpForm", "\345\234\250\347\263\273\347\273\237\344\270\255\347\232\204\350\272\253\344\273\275", nullptr));
        prompt->setText(QString());
        label_4->setText(QCoreApplication::translate("SignUpForm", "              \346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUpForm: public Ui_SignUpForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPFORM_H
