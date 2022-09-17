/********************************************************************************
** Form generated from reading UI file 'signupform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPFORM_H
#define UI_SIGNUPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            SignUpForm->setObjectName(QStringLiteral("SignUpForm"));
        SignUpForm->resize(400, 300);
        cancelButton = new QPushButton(SignUpForm);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(189, 209, 93, 28));
        confirmButton = new QPushButton(SignUpForm);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(90, 209, 93, 28));
        layoutWidget = new QWidget(SignUpForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(159, 89, 173, 81));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        userName = new QLineEdit(layoutWidget);
        userName->setObjectName(QStringLiteral("userName"));

        verticalLayout->addWidget(userName);

        password = new QLineEdit(layoutWidget);
        password->setObjectName(QStringLiteral("password"));

        verticalLayout->addWidget(password);

        identity = new QLineEdit(layoutWidget);
        identity->setObjectName(QStringLiteral("identity"));

        verticalLayout->addWidget(identity);

        layoutWidget_2 = new QWidget(SignUpForm);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(39, 89, 107, 81));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        label = new QLabel(layoutWidget_2);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(9);
        label->setFont(font);
        label->setIndent(0);

        verticalLayout_2->addWidget(label);

        prompt = new QLabel(SignUpForm);
        prompt->setObjectName(QStringLiteral("prompt"));
        prompt->setGeometry(QRect(110, 179, 151, 20));
        label_4 = new QLabel(SignUpForm);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 50, 166, 32));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(16);
        label_4->setFont(font1);

        retranslateUi(SignUpForm);

        QMetaObject::connectSlotsByName(SignUpForm);
    } // setupUi

    void retranslateUi(QWidget *SignUpForm)
    {
        SignUpForm->setWindowTitle(QApplication::translate("SignUpForm", "Form", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("SignUpForm", "\345\217\226\346\266\210", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("SignUpForm", "\347\241\256\350\256\244", Q_NULLPTR));
        label_2->setText(QApplication::translate("SignUpForm", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("SignUpForm", "\345\257\206\347\240\201", Q_NULLPTR));
        label->setText(QApplication::translate("SignUpForm", "\345\234\250\347\263\273\347\273\237\344\270\255\347\232\204\350\272\253\344\273\275", Q_NULLPTR));
        prompt->setText(QString());
        label_4->setText(QApplication::translate("SignUpForm", "              \346\263\250\345\206\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignUpForm: public Ui_SignUpForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPFORM_H
