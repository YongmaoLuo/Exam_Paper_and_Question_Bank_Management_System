#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include<QDir>
#include <QTextStream>
#include <QCryptographicHash>
#include "rulemakerdialog.h"
#include "admindialog.h"
#include "ui_admindialog.h"
#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "ownInterface.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password); // 设置密码框显示模式。
}

LoginDialog::~LoginDialog()
{
    delete ui;
    //delete adminPanel;
    //delete ruleMakerPanel;
    //delete signUpPanel;
}

void LoginDialog::on_loginButton_clicked()
{
    QString user = ui->userName->text(); // 用户名是密码文件的文件名。
    QString pass=ui->password->text();
    submit_login(user,pass);
}

void LoginDialog::submit_login(QString userName, QString password){
    // 非空校验
    if(userName.trimmed().length()==0){
        ui->prompt->setText("用户名为空");
        ui->userName->setFocus();
        return;
    }
    if(password.trimmed().length()==0){
        ui->prompt->setText("密码为空");
        ui->password->setFocus();
        return;
    }

    // 读取用户密码文件
    QFile inputFile("./User/" + userName.trimmed());
    bool isExist=inputFile.exists();
    if(!isExist){
        ui->prompt->setText("没有此用户"+userName.trimmed());
        ui->userName->setFocus();
        return;
    }
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    QString cipherText = in.readAll(); // 加密后的密码串。
    inputFile.close();
    QByteArray temp=password.toLocal8Bit();
    if(cipherText.trimmed()==QCryptographicHash::hash(("admin"+password).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex()){
        // 登录成功，身份是管理员
        store_login_information(userName,"admin");
        adminPanel=new AdminDialog(this);
        // 此双向连接用于关闭窗口时的模块之间交互
        connect(adminPanel,&AdminDialog::admin_panel_be_closed,this,&LoginDialog::receive_admin_panel_closure);
        connect(this,&LoginDialog::login_close_admin,adminPanel,&AdminDialog::close_admin_panel);
        adminPanel->open_admin_panel();
        this->hide();
    }else if(cipherText.trimmed()==QCryptographicHash::hash(("teacher"+password).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex()){
        // 登录成功，身份为教师
        store_login_information(userName,"teacher");
        mainwindowPanel=new MainWindow(this);
        connect(mainwindowPanel,&MainWindow::teacher_panel_be_closed,this,&LoginDialog::receive_teacher_panel_closure);
        connect(this,&LoginDialog::login_close_teacher,mainwindowPanel,&MainWindow::close_question_management_panel);
        mainwindowPanel->open_question_management_panel();
        this->hide();
    }else if(cipherText.trimmed()==QCryptographicHash::hash(("rulemaker"+password).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex()){
        // 登录成功，身份为试卷规则制定者
        store_login_information(userName,"rulemaker");
        this->hide();
        rulemakerDir=new QDir("./Bulletin/"+userName);
        QString identityString="rulemaker";
        ruleMakerPanel=new RuleMakerDialog(this,&userName,&identityString);
        // 此双向连接用于关闭窗口时的模块之间交互
        connect(ruleMakerPanel,&RuleMakerDialog::rulemaker_panel_be_closed,this,&LoginDialog::receive_rulemaker_panel_closure);
        connect(this,&LoginDialog::login_close_rulemaker,ruleMakerPanel,&RuleMakerDialog::close_rulemaker_panel);
        ruleMakerPanel->open_rulemaker_panel();
    }else{
        ui->prompt->setText("密码错误"+cipherText.trimmed());
        ui->password->setFocus();
        return;
    }
}

void LoginDialog::on_registerButton_clicked()
{
    this->hide();
    signUpPanel=new SignUpDialog(this);
    // 此双向连接用于关闭窗口时的模块之间交互
    connect(signUpPanel,&SignUpDialog::signup_panel_be_closed,this,&LoginDialog::receive_signup_panel_closure);
    connect(this,&LoginDialog::login_close_signup,signUpPanel,&SignUpDialog::close_signup_panel);
    signUpPanel->open_signup_panel();
}

void LoginDialog::open_login_panel(){
    this->setWindowTitle("登录");
    this->show();
}

void LoginDialog::receive_signup_panel_closure(){
    signUpPanel=nullptr;
    emit login_close_signup();
}

void LoginDialog::receive_admin_panel_closure(){
    adminPanel=nullptr;
    emit login_close_admin();
}

void LoginDialog::store_login_information(QString userName, QString identity){
    this->userName=userName;
    this->identity=identity;
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
