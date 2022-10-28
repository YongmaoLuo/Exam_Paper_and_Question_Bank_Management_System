/********************************************************************************
** Form generated from reading UI file 'signupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPDIALOG_H
#define UI_SIGNUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
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
            SignUpDialog->setObjectName(QStringLiteral("SignUpDialog"));
        SignUpDialog->resize(409, 316);
        label_4 = new QLabel(SignUpDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(51, 71, 166, 32));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(16);
        label_4->setFont(font);
        confirmButton = new QPushButton(SignUpDialog);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(91, 230, 93, 28));
        cancelButton = new QPushButton(SignUpDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(190, 230, 93, 28));
        layoutWidget = new QWidget(SignUpDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 110, 173, 81));
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

        layoutWidget1 = new QWidget(SignUpDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 110, 107, 81));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(9);
        label->setFont(font1);
        label->setIndent(0);

        verticalLayout_2->addWidget(label);

        prompt = new QLabel(SignUpDialog);
        prompt->setObjectName(QStringLiteral("prompt"));
        prompt->setGeometry(QRect(111, 200, 151, 20));

        retranslateUi(SignUpDialog);

        QMetaObject::connectSlotsByName(SignUpDialog);
    } // setupUi

    void retranslateUi(QDialog *SignUpDialog)
    {
        SignUpDialog->setWindowTitle(QApplication::translate("SignUpDialog", "Dialog", Q_NULLPTR));
        label_4->setText(QApplication::translate("SignUpDialog", "              \346\263\250\345\206\214", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("SignUpDialog", "\347\241\256\350\256\244", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("SignUpDialog", "\345\217\226\346\266\210", Q_NULLPTR));
        label_2->setText(QApplication::translate("SignUpDialog", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("SignUpDialog", "\345\257\206\347\240\201", Q_NULLPTR));
        label->setText(QApplication::translate("SignUpDialog", "\345\234\250\347\263\273\347\273\237\344\270\255\347\232\204\350\272\253\344\273\275", Q_NULLPTR));
        prompt->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignUpDialog: public Ui_SignUpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPDIALOG_H
