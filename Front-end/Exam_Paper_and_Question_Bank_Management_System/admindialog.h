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
    void on_agreeButton_clicked();
    void on_rejectButton_clicked();
    void on_deleteButton_clicked();

    void set_application_button_enable();
    void on_userListWidget_itemSelectionChanged();
public slots:
    void close_admin_panel() override;

private:
    Ui::AdminDialog *ui;
    QDir applicantsDir;
    QDir usersDir;
    void read_applicants(QDir applicantsDir) override;
    void read_users(QDir usersDir) override;
    void agree_applicant(QString applicantName) override;
    void reject_applicant(QString applicantName) override;
    void delete_user(QString userName) override;

};

#endif // ADMINDIALOG_H
