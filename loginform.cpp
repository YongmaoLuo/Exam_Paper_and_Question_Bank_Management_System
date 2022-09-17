#include "loginform.h"
#include "ui_loginform.h"
#include <QFile>
#include<QDir>
#include <QTextStream>
#include <QCryptographicHash>
#include "rulemakerdialog.h"
#include "admindialog.h"
#include "ui_admindialog.h"
#include "signupform.h"
#include "ui_signupform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    AdminDialog adminPanel(this);
    adminPanel.setWindowTitle("管理界面");
    RuleMakerDialog ruleMakerPanel(this);
    ruleMakerPanel.setWindowTitle("试卷规则制定");
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_loginButton_clicked()
{
    QString user = ui->userName->text(); // 用户名是密码文件的文件名。
    QString pass=ui->password->text();
    // 非空校验
    if(user.trimmed().length()==0){
        ui->prompt->setText("用户名为空");
        ui->userName->setFocus();
        return;
    }
    if(pass.trimmed().length()==0){
        ui->prompt->setText("密码为空");
        ui->password->setFocus();
        return;
    }

    // 读取用户密码文件
    QFile inputFile("./User/" + user.trimmed());
    bool isExist=inputFile.exists();
    if(!isExist){
        ui->prompt->setText("没有此用户"+user.trimmed());
        ui->userName->setFocus();
        return;
    }
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    in.setCodec("UTF-8");
    QString cipherText = in.readAll(); // 加密后的密码串。
    inputFile.close();
    QByteArray temp=pass.toLocal8Bit();
    if(cipherText.trimmed()==QCryptographicHash::hash(("admin"+pass).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex()){
        // 登录成功，身份是管理员
        LoginForm::adminPanel.show();
        this->hide();
    }else if(cipherText.trimmed()==QCryptographicHash::hash(("teacher"+pass).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex()){
        // 登录成功，身份为教师
        this->close();
        parentWidget()->show();
    }else if(cipherText.trimmed()==QCryptographicHash::hash(("ruleMaker"+pass).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex()){
        // 登录成功，身份为试卷规则制定者
        this->hide();
        ruleMakerPanel.show();
    }else{
        ui->prompt->setText("密码错误"+cipherText.trimmed());
        ui->password->setFocus();
        return;
    }
}


void LoginForm::on_registerButton_clicked()
{
    //this->hide();
    signUpPanel=new SignUpForm(this);
    signUpPanel->setWindowModality(Qt::NonModal);
    signUpPanel->setWindowTitle("注册确认");
    signUpPanel->show();
}

