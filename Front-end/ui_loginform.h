/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QPushButton *registerButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *userName;
    QLineEdit *password;
    QLabel *label;
    QLabel *prompt;
    QPushButton *loginButton;

    void setupUi(QWidget *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName(QStringLiteral("LoginForm"));
        LoginForm->resize(831, 619);
        registerButton = new QPushButton(LoginForm);
        registerButton->setObjectName(QStringLiteral("registerButton"));
        registerButton->setGeometry(QRect(340, 420, 93, 28));
        layoutWidget = new QWidget(LoginForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(280, 280, 228, 52));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        userName = new QLineEdit(layoutWidget);
        userName->setObjectName(QStringLiteral("userName"));

        verticalLayout->addWidget(userName);

        password = new QLineEdit(layoutWidget);
        password->setObjectName(QStringLiteral("password"));

        verticalLayout->addWidget(password);


        horizontalLayout->addLayout(verticalLayout);

        label = new QLabel(LoginForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 180, 561, 47));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(28);
        label->setFont(font);
        label->setScaledContents(true);
        label->setWordWrap(false);
        label->setMargin(0);
        label->setIndent(20);
        label->setOpenExternalLinks(false);
        prompt = new QLabel(LoginForm);
        prompt->setObjectName(QStringLiteral("prompt"));
        prompt->setGeometry(QRect(290, 340, 201, 20));
        loginButton = new QPushButton(LoginForm);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(330, 370, 121, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        loginButton->setFont(font1);
#ifndef QT_NO_SHORTCUT
#endif // QT_NO_SHORTCUT

        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QWidget *LoginForm)
    {
        LoginForm->setWindowTitle(QApplication::translate("LoginForm", "Form", Q_NULLPTR));
        registerButton->setText(QApplication::translate("LoginForm", "\346\263\250\345\206\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginForm", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("LoginForm", "\345\257\206\347\240\201", Q_NULLPTR));
        label->setText(QApplication::translate("LoginForm", "\345\207\272\345\215\267\345\222\214\351\242\230\345\272\223\347\256\241\347\220\206\347\263\273\347\273\237", Q_NULLPTR));
        prompt->setText(QString());
        loginButton->setText(QApplication::translate("LoginForm", "\347\231\273\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
