#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "admindialog.h"
#include "rulemakerdialog.h"
#include "signupdialog.h"
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog,public Login
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void open_login_panel() override;

signals:
    void login_close_signup();
    void login_close_admin();
    void login_close_rulemaker();
    void login_close_teacher();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

    void receive_signup_panel_closure();
    void receive_admin_panel_closure();
    void receive_rulemaker_panel_closure();
    void receive_teacher_panel_closure();

private:
    Ui::LoginDialog *ui;
    AdminDialog *adminPanel;
    RuleMakerDialog *ruleMakerPanel;
    SignUpDialog *signUpPanel;
    MainWindow *mainwindowPanel;
    QDir *rulemakerDir;
    void submit_login(QString userName, QString password) override;
    void store_login_information(QString userName, QString identity) override;
};

#endif // LOGINDIALOG_H
