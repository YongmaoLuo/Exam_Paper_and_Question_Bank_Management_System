#include "signupform.h"
#include "ui_signupform.h"
#include <QFile>
#include <QCryptographicHash>
#include <QTextStream>
#include <QMessageBox>

SignUpForm::SignUpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpForm)
{
    ui->setupUi(this);
}

SignUpForm::~SignUpForm()
{
    delete ui;
}

void SignUpForm::on_confirmButton_clicked()
{
    QString user = ui->userName->text(); // 用户名是密码文件的文件名。
    QString pass=ui->password->text();
    QString iden=ui->identity->text();
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
    if(iden.trimmed().length()==0){
        ui->prompt->setText("用户身份为空");
        ui->identity->setFocus();
        return;
    }

    // 判断用户名是否存在
    QFile userExists("./User/"+user.trimmed());
    if(userExists.exists()){
        ui->prompt->setText("用户名已被注册");
        ui->userName->setFocus();
        return;
    }

    QByteArray userCipherHex;
    //为不同身份制作不同的哈希值
    if(iden=="admin"){
        userCipherHex=QCryptographicHash::hash(("admin"+pass).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex();
    }else if(iden=="teacher"){
        userCipherHex=QCryptographicHash::hash(("teacher"+pass).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex();
    }else if(iden=="ruleMaker"){
        userCipherHex=QCryptographicHash::hash(("ruleMaker"+pass).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex();
    }else{
        ui->prompt->setText("用户身份不存在");
        ui->identity->setFocus();
        return;
    }

    QFile signUpWrite("./SignUp/"+user.trimmed());
    if(signUpWrite.exists()){
        ui->prompt->setText("用户正在注册中");
        ui->userName->setFocus();
        return;
    }
    signUpWrite.open(QIODevice::WriteOnly);
    QTextStream signUpStream(&signUpWrite);
    signUpStream.setCodec("UTF-8");
    signUpStream<<userCipherHex;
}

void SignUpForm::on_cancelButton_clicked()
{
    this->hide();
    parentWidget()->show();
}
