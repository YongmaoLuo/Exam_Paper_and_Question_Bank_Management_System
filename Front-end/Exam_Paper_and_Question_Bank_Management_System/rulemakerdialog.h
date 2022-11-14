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
    explicit RuleMakerDialog(QWidget *parent = nullptr, TCPClientSocket *client=nullptr);
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

public slots:
    void close_rulemaker_panel() override;// close the window

private:
    Ui::RuleMakerDialog *ui;
    TCPClientSocket *client;
    QString tempBulletinName,tempBulletinText;
    void delete_bulletin(QString fileName) override;// delete selected bulletin
    void load_bulletin(QString fileName) override;// load the bulletin into text editor
    void write_bulletin(QString fileName,QString bulletinText) override;// submit modification of the bulletin
    void read_bulletins() override;// read all the bulletin
    void create_bulletin(QString teacherName, QString timeStamp) override;
};

#endif // RULEMAKERDIALOG_H
