#ifndef PAPERPRODUCTIONDIALOG_H
#define PAPERPRODUCTIONDIALOG_H

#include <QDialog>
#include <QCloseEvent>;
#include <QListWidgetItem>
#include "ownInterface.h"

namespace Ui {
class PaperProductionDialog;
}

class PaperProductionDialog : public QDialog, public PaperProduction
{
    Q_OBJECT

signals:
    void paper_production_panel_be_closed();

public:
    explicit PaperProductionDialog(QWidget *parent = nullptr);
    ~PaperProductionDialog();
    void add_question(QString subject,QString chapter,QString timeStamp) override;
    void open_paper_production_panel() override;

private slots:
    void on_hideButton_clicked();
    void closeEvent( QCloseEvent * event);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_deleteButton_clicked();

    void on_outputButton_clicked();

public slots:
    void close_paper_production_panel() override;

private:
    Ui::PaperProductionDialog *ui;
    void delete_question(QString questionName) override;// 在试卷中删除某题目
    void output_paper(QDir paperDir,QStringList questionsList) override;// 输出试卷
    void read_questions(QStringList questionsList) override;

};

#endif // PAPERPRODUCTIONDIALOG_H
