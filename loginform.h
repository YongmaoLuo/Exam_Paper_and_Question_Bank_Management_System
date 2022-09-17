#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QDialog>
#include "rulemakerdialog.h"
#include "signupform.h"
#include "admindialog.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::LoginForm *ui;
    AdminDialog adminPanel;
    RuleMakerDialog ruleMakerPanel;
    SignUpForm *signUpPanel;
};

#endif // LOGINFORM_H
