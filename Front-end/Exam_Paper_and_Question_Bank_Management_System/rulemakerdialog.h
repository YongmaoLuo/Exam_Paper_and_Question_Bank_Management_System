#ifndef RULEMAKERDIALOG_H
#define RULEMAKERDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "ownInterface.h"

namespace Ui {
class RuleMakerDialog;
}

class RuleMakerDialog : public QDialog, public RuleMaker
{
    Q_OBJECT

public:
    explicit RuleMakerDialog(QWidget *parent = nullptr, std::unique_ptr<TCPClientSocket> client=nullptr);
    ~RuleMakerDialog();
    void open_rulemaker_panel() override;

signals:
    void rulemaker_panel_be_closed();

private slots:
    void on_submitButton_clicked();
    void on_exitButton_clicked();
    void on_bulletinListWidget_itemSelectionChanged();
    void on_bulletinListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_deleteButton_clicked();
    void on_createButton_clicked();

    void on_teacherListWidget_itemSelectionChanged();

public slots:
    void close_rulemaker_panel() override;// close the window

private:
    Ui::RuleMakerDialog *ui;
    std::unique_ptr<TCPClientSocket> client;
    void delete_bulletin(QString bulletinName) override;// delete selected bulletin
    void read_bulletin(QString bulletinName) override;// load the bulletin into text editor
    void write_bulletin(QString bulletinName,QString bulletinText) override;// submit modification of the bulletin
    void get_bulletins() override;// read all the bulletin
    void create_bulletin(QString teacherName, QString timeStamp) override;
    void get_teachers() override;
};

#endif // RULEMAKERDIALOG_H
