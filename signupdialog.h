#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "ownInterface.h"

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog,public SignUp
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();
    void open_signup_panel() override;

signals:
    void signup_panel_be_closed();

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
    void on_userName_textEdited(const QString &arg1);

public slots:
    void close_signup_panel() override;

private:
    Ui::SignUpDialog *ui;
    void submit_signup(QString userName, QString password, QString identity) override;

};

#endif // SIGNUPDIALOG_H
