#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDir>
#include <QListWidgetItem>
#include "ownInterface.h"
#include "rulemakerdialog.h"
#include "paperproductiondialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,public QuestionManagement
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,std::unique_ptr<TCPClientSocket> client=nullptr);
    ~MainWindow();

signals:
    void teacher_panel_be_closed();
    void teacher_close_rulemaker();
    void add_question_to_paper(QString subject,QString chapter,QString timeStamp);
    void teacher_close_paper_production();

private slots:
    void on_subjectDeleteButton_clicked();
    void on_subjectCreateButton_clicked();
    void on_chapterDeleteButton_clicked();
    void on_chapterCreateButton_clicked();
    void on_storeButton_clicked();
    void on_questionDeleteButton_clicked();
    void on_questionCreateButton_clicked();
    void on_subjectListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_chapterListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_questionListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_exitButton_clicked();
    void on_subjectListWidget_itemClicked(QListWidgetItem *item);
    void on_chapterListWidget_itemClicked(QListWidgetItem *item);
    void on_questionListWidget_itemClicked(QListWidgetItem *item);
    void on_bulletinAction_triggered();
    void on_makePaperAction_triggered();

    void receive_rulemaker_panel_closure();
    void receive_paper_production_panel_closure();

    void on_addPaperButton_clicked();

public slots:
    void close_question_management_panel() override;

private:
    Ui::MainWindow *ui;
    std::unique_ptr<TCPClientSocket> client;
    RuleMakerDialog *rulemakerPanel=nullptr;
    PaperProductionDialog *paperPanel=nullptr;
    bool canMakePaper=false;
    void get_subjects() override;
    void get_chapters(QString subject) override;
    void get_questions(QString subject,QString chapter) override;
    void add_subject(QString subject) override;
    void add_chapter(QString subject,QString chapter) override;
    void add_question(QString subject,QString chapter,QString timeStamp) override;
    void delete_subject(QString subject) override;
    void delete_chapter(QString subject,QString chapter) override;
    void delete_question(QString subject,QString chapter,QString timeStamp) override;
    void read_question(QString subject,QString chapter,QString timeStamp) override;
    void write_question(QString subject,QString chapter,QString timeStamp,QString questionText) override;

public:
    void open_question_management_panel() override;
};
#endif // MAINWINDOW_H
