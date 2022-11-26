#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "ownInterface.h"

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog,public Admin
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = nullptr,std::unique_ptr<TCPClientSocket> client=nullptr);
    ~AdminDialog();
    void open_admin_panel() override;

signals:
    void admin_panel_be_closed();
private slots:
    void on_exitButton_clicked();
    void on_registerButton_clicked();
    void on_deleteButton_clicked();

    void on_userListWidget_itemSelectionChanged();
    void on_checkBoxAdmin_pressed();

    void on_checkBoxTeacher_pressed();

    void on_checkBoxRuleMaker_pressed();

public slots:
    void close_admin_panel() override;

private:
    Ui::AdminDialog *ui;
    std::unique_ptr<TCPClientSocket> client;
    void read_users() override;
    void delete_user(QString userName) override;
    void register_user(QString userName, QString password) override;
};

#endif // ADMINDIALOG_H
