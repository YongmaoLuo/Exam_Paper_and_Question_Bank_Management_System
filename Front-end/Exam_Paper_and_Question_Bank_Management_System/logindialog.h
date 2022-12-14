#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "admindialog.h"
#include "rulemakerdialog.h"
#include "mainwindow.h"

namespace Ui { // there is another ui_logindialog.h file created by user interface compiler by Qt
class LoginDialog;
}

class LoginDialog : public QDialog,public Login
{
    Q_OBJECT // indicate it should be handled by signal-slot mechanism

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

    void receive_admin_panel_closure();
    void receive_rulemaker_panel_closure();
    void receive_teacher_panel_closure();

private:
    Ui::LoginDialog *ui;
    std::unique_ptr<AdminDialog> adminPanel;
    std::unique_ptr<RuleMakerDialog> ruleMakerPanel;
    std::unique_ptr<MainWindow> mainwindowPanel;
    void submit_login(QString userName, QString password) override;
};

#endif // LOGINDIALOG_H
