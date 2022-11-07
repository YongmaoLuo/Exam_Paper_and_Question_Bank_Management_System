#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include<QDir>
#include <QTextStream>
#include <QCryptographicHash>
#include "rulemakerdialog.h"
#include "admindialog.h"
#include "ownInterface.h"
#include <QMessageBox>
#include <tcpclientsocket.h>
#include <stdio.h>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password); // hide type in text because it is password
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    QString user = ui->userName->text();
    QString pass=ui->password->text();
    submit_login(user,pass);
}

void LoginDialog::submit_login(QString userName, QString password){
    // check if the entered username or password is empty
    if(userName.trimmed().length()==0){
        ui->prompt->setText("username is empty");
        ui->userName->setFocus();
        return;
    }
    if(password.trimmed().length()==0){
        ui->prompt->setText("password is empty");
        ui->password->setFocus();
        return;
    }

    TCPClientSocket *client=new TCPClientSocket();
    if(client->updateServerAddress("127.0.0.1",9999)==-1){
        QMessageBox::warning(this, "warning", "fail to update address");
        return;
    }
    if(client->connectToServer()==-1){
        perror("error:");
        QMessageBox::warning(this, "warning", QString::fromUtf8(fmt::format("fail to connect to server. errno:{}",errno).c_str()));
        return;
    }

    // encryption: QCryptographicHash::hash((password).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex().toStdString()
    std::string rawJson=fmt::format("{{\"command\": \"{}\", \"username\": \"{}\", \"password\": \"{}\"}}","login",
                                    userName.toStdString(),password.toStdString());
    json packet=json::parse(rawJson);
    if(client->sendToServer(packet)==-1){
        QMessageBox::warning(this, "warning", "fail to request login to server");
        return;
    }
    if(client->receive(packet)==-1){
        QMessageBox::warning(this, "warning", "fail to receive message from server");
        return;
    }
    if(packet["code"]==200){
        if(packet["identity"]=="admin"){
            adminPanel=new AdminDialog(this,client);
            // signal-slot connection between adminPanel and loginPanel, since loginPanel control all generated widgets
            connect(adminPanel,&AdminDialog::admin_panel_be_closed,this,&LoginDialog::receive_admin_panel_closure);
            connect(this,&LoginDialog::login_close_admin,adminPanel,&AdminDialog::close_admin_panel);
            adminPanel->open_admin_panel();
            this->hide();
        }else if(packet["identity"]=="teacher"){
            mainwindowPanel=new MainWindow(this,client);
            connect(mainwindowPanel,&MainWindow::teacher_panel_be_closed,this,&LoginDialog::receive_teacher_panel_closure);
            connect(this,&LoginDialog::login_close_teacher,mainwindowPanel,&MainWindow::close_question_management_panel);
            mainwindowPanel->open_question_management_panel();
            this->hide();
        }else if(packet["identity"]=="rulemaker"){
            ruleMakerPanel=new RuleMakerDialog(this,client);
            // signal-slot connections for closing rulemaker panel
            connect(ruleMakerPanel,&RuleMakerDialog::rulemaker_panel_be_closed,this,&LoginDialog::receive_rulemaker_panel_closure);
            connect(this,&LoginDialog::login_close_rulemaker,ruleMakerPanel,&RuleMakerDialog::close_rulemaker_panel);
            ruleMakerPanel->open_rulemaker_panel();
            this->hide();
        }else{
            QMessageBox::warning(this, "warning", "undefined message from server side");
            return;
        }
    }else if(packet["code"]==403){
        QMessageBox::warning(this, "warning", "password incorrect");
        ui->password->setFocus();
    }else if(packet["code"]==404){
        QMessageBox::warning(this, "warning", "user not exist");
        ui->userName->setFocus();
    }else{
        QMessageBox::warning(this, "warning", "undefined message from server side");
    }

}

void LoginDialog::open_login_panel(){
    this->setWindowTitle("Login Panel");
    this->show();
}

//void LoginDialog::receive_signup_panel_closure(){
//    signUpPanel=nullptr;
//    emit login_close_signup();
//}

void LoginDialog::receive_admin_panel_closure(){
    adminPanel=nullptr;
    emit login_close_admin();
}

void LoginDialog::receive_rulemaker_panel_closure(){
    rulemakerDir=nullptr;
    ruleMakerPanel=nullptr;
    emit login_close_rulemaker();
}

void LoginDialog::receive_teacher_panel_closure(){
    mainwindowPanel=nullptr;
    emit login_close_teacher();
}
