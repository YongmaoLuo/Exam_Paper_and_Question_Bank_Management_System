/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *bulletinAction;
    QAction *makePaperAction;
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *storeButton;
    QListWidget *subjectListWidget;
    QListWidget *chapterListWidget;
    QPushButton *subjectDeleteButton;
    QPushButton *subjectCreateButton;
    QPushButton *chapterDeleteButton;
    QPushButton *chapterCreateButton;
    QListWidget *questionListWidget;
    QLabel *label;
    QPushButton *questionCreateButton;
    QPushButton *questionDeleteButton;
    QPushButton *exitButton;
    QPushButton *addPaperButton;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(841, 629);
        bulletinAction = new QAction(MainWindow);
        bulletinAction->setObjectName(QString::fromUtf8("bulletinAction"));
        makePaperAction = new QAction(MainWindow);
        makePaperAction->setObjectName(QString::fromUtf8("makePaperAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(580, 60, 221, 391));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 20, 40, 23));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        label_2->setFont(font);
        label_2->setIndent(0);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(270, 20, 88, 23));
        label_3->setMinimumSize(QSize(88, 0));
        label_3->setFont(font);
        label_3->setIndent(0);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(670, 20, 40, 23));
        label_4->setFont(font);
        label_4->setIndent(0);
        storeButton = new QPushButton(centralwidget);
        storeButton->setObjectName(QString::fromUtf8("storeButton"));
        storeButton->setGeometry(QRect(640, 460, 93, 28));
        subjectListWidget = new QListWidget(centralwidget);
        subjectListWidget->setObjectName(QString::fromUtf8("subjectListWidget"));
        subjectListWidget->setGeometry(QRect(40, 60, 161, 391));
        chapterListWidget = new QListWidget(centralwidget);
        chapterListWidget->setObjectName(QString::fromUtf8("chapterListWidget"));
        chapterListWidget->setGeometry(QRect(220, 60, 161, 391));
        subjectDeleteButton = new QPushButton(centralwidget);
        subjectDeleteButton->setObjectName(QString::fromUtf8("subjectDeleteButton"));
        subjectDeleteButton->setGeometry(QRect(40, 460, 71, 28));
        subjectCreateButton = new QPushButton(centralwidget);
        subjectCreateButton->setObjectName(QString::fromUtf8("subjectCreateButton"));
        subjectCreateButton->setGeometry(QRect(120, 460, 71, 28));
        chapterDeleteButton = new QPushButton(centralwidget);
        chapterDeleteButton->setObjectName(QString::fromUtf8("chapterDeleteButton"));
        chapterDeleteButton->setGeometry(QRect(230, 460, 71, 28));
        chapterCreateButton = new QPushButton(centralwidget);
        chapterCreateButton->setObjectName(QString::fromUtf8("chapterCreateButton"));
        chapterCreateButton->setGeometry(QRect(310, 460, 71, 28));
        questionListWidget = new QListWidget(centralwidget);
        questionListWidget->setObjectName(QString::fromUtf8("questionListWidget"));
        questionListWidget->setGeometry(QRect(400, 60, 161, 391));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(460, 20, 40, 23));
        label->setFont(font);
        questionCreateButton = new QPushButton(centralwidget);
        questionCreateButton->setObjectName(QString::fromUtf8("questionCreateButton"));
        questionCreateButton->setGeometry(QRect(490, 460, 71, 28));
        questionDeleteButton = new QPushButton(centralwidget);
        questionDeleteButton->setObjectName(QString::fromUtf8("questionDeleteButton"));
        questionDeleteButton->setGeometry(QRect(410, 460, 71, 28));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(350, 520, 93, 41));
        addPaperButton = new QPushButton(centralwidget);
        addPaperButton->setObjectName(QString::fromUtf8("addPaperButton"));
        addPaperButton->setGeometry(QRect(470, 500, 91, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 841, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(bulletinAction);
        menu->addAction(makePaperAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        bulletinAction->setText(QCoreApplication::translate("MainWindow", "Bulletin Board", nullptr));
        makePaperAction->setText(QCoreApplication::translate("MainWindow", "Make Test paper", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\247\221\347\233\256", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\253\240\350\212\202", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\226\207\346\234\254", nullptr));
        storeButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        subjectDeleteButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        subjectCreateButton->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        chapterDeleteButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        chapterCreateButton->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\242\230\347\233\256", nullptr));
        questionCreateButton->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        questionDeleteButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        addPaperButton->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\350\207\263\350\257\225\345\215\267", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\212\237\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
