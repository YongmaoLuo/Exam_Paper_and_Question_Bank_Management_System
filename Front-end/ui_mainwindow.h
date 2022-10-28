/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(841, 629);
        bulletinAction = new QAction(MainWindow);
        bulletinAction->setObjectName(QStringLiteral("bulletinAction"));
        makePaperAction = new QAction(MainWindow);
        makePaperAction->setObjectName(QStringLiteral("makePaperAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(580, 60, 221, 391));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 20, 40, 23));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        label_2->setFont(font);
        label_2->setIndent(0);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(270, 20, 88, 23));
        label_3->setMinimumSize(QSize(88, 0));
        label_3->setFont(font);
        label_3->setIndent(0);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(670, 20, 40, 23));
        label_4->setFont(font);
        label_4->setIndent(0);
        storeButton = new QPushButton(centralwidget);
        storeButton->setObjectName(QStringLiteral("storeButton"));
        storeButton->setGeometry(QRect(640, 460, 93, 28));
        subjectListWidget = new QListWidget(centralwidget);
        subjectListWidget->setObjectName(QStringLiteral("subjectListWidget"));
        subjectListWidget->setGeometry(QRect(40, 60, 161, 391));
        chapterListWidget = new QListWidget(centralwidget);
        chapterListWidget->setObjectName(QStringLiteral("chapterListWidget"));
        chapterListWidget->setGeometry(QRect(220, 60, 161, 391));
        subjectDeleteButton = new QPushButton(centralwidget);
        subjectDeleteButton->setObjectName(QStringLiteral("subjectDeleteButton"));
        subjectDeleteButton->setGeometry(QRect(40, 460, 71, 28));
        subjectCreateButton = new QPushButton(centralwidget);
        subjectCreateButton->setObjectName(QStringLiteral("subjectCreateButton"));
        subjectCreateButton->setGeometry(QRect(120, 460, 71, 28));
        chapterDeleteButton = new QPushButton(centralwidget);
        chapterDeleteButton->setObjectName(QStringLiteral("chapterDeleteButton"));
        chapterDeleteButton->setGeometry(QRect(230, 460, 71, 28));
        chapterCreateButton = new QPushButton(centralwidget);
        chapterCreateButton->setObjectName(QStringLiteral("chapterCreateButton"));
        chapterCreateButton->setGeometry(QRect(310, 460, 71, 28));
        questionListWidget = new QListWidget(centralwidget);
        questionListWidget->setObjectName(QStringLiteral("questionListWidget"));
        questionListWidget->setGeometry(QRect(400, 60, 161, 391));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(460, 20, 40, 23));
        label->setFont(font);
        questionCreateButton = new QPushButton(centralwidget);
        questionCreateButton->setObjectName(QStringLiteral("questionCreateButton"));
        questionCreateButton->setGeometry(QRect(490, 460, 71, 28));
        questionDeleteButton = new QPushButton(centralwidget);
        questionDeleteButton->setObjectName(QStringLiteral("questionDeleteButton"));
        questionDeleteButton->setGeometry(QRect(410, 460, 71, 28));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(350, 520, 93, 41));
        addPaperButton = new QPushButton(centralwidget);
        addPaperButton->setObjectName(QStringLiteral("addPaperButton"));
        addPaperButton->setGeometry(QRect(470, 500, 91, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 841, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(bulletinAction);
        menu->addAction(makePaperAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        bulletinAction->setText(QApplication::translate("MainWindow", "Bulletin Board", Q_NULLPTR));
        makePaperAction->setText(QApplication::translate("MainWindow", "Make Test paper", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\347\247\221\347\233\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\347\253\240\350\212\202", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\346\226\207\346\234\254", Q_NULLPTR));
        storeButton->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        subjectDeleteButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        subjectCreateButton->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", Q_NULLPTR));
        chapterDeleteButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        chapterCreateButton->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\351\242\230\347\233\256", Q_NULLPTR));
        questionCreateButton->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", Q_NULLPTR));
        questionDeleteButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        exitButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        addPaperButton->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\350\207\263\350\257\225\345\215\267", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\345\212\237\350\203\275", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
