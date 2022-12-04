#ifndef PAPERPRODUCTIONDIALOG_H
#define PAPERPRODUCTIONDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QStandardPaths>
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
    explicit PaperProductionDialog(QWidget *parent = nullptr,std::shared_ptr<TCPClientSocket> client = nullptr);
    ~PaperProductionDialog();
    void add_question(QString subject,QString chapter,QString timeStamp) override;
    void open_paper_production_panel() override;

private slots:
    void on_hideButton_clicked();
    void closeEvent( QCloseEvent * event) override;

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_deleteButton_clicked();

    void on_outputButton_clicked();

public slots:
    void close_paper_production_panel() override;

private:
    Ui::PaperProductionDialog *ui;
    std::shared_ptr<TCPClientSocket> client;
    void delete_question(QString questionName) override;// delete question in paper
    void output_paper(QString pathName,QStringList questionsList) override;// output the paper into a file in desktop directory
    void read_questions(QStringList questionsList) override; // load questions in the list into the GUI

};

#endif // PAPERPRODUCTIONDIALOG_H
