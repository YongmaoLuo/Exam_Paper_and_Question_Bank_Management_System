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
    explicit AdminDialog(QWidget *parent = nullptr,TCPClientSocket *client=nullptr);
    ~AdminDialog();
    void open_admin_panel() override;

signals:
    void admin_panel_be_closed();
private slots:
    void on_exitButton_clicked();
    void on_registerButton_clicked();
    void on_deleteButton_clicked();

    void on_userListWidget_itemSelectionChanged();
public slots:
    void close_admin_panel() override;

private:
    Ui::AdminDialog *ui;
    TCPClientSocket *client;
    QList<QString> users;
    void read_users() override;
    void delete_user(QString userName) override;
    void register_user(QString userName, QString password) override;
};

#endif // ADMINDIALOG_H
