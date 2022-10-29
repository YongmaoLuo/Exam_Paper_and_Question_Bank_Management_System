#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QFile>
#include <QCryptographicHash>
#include <QTextStream>
#include <QMessageBox>

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_confirmButton_clicked()
{
    QString userName = ui->userName->text(); // 用户名是密码文件的文件名的一部分
    QString password=ui->password->text();
    QString identity=ui->identity->text();
    submit_signup(userName,password,identity);

}

void SignUpDialog::submit_signup(QString userName, QString password, QString identity){
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
    if(identity.trimmed().length()==0){
        ui->prompt->setText("用户身份为空");
        ui->identity->setFocus();
        return;
    }

    // 判断用户名是否存在
    QFile userExists("./User/"+userName.trimmed());
    if(userExists.exists()){
        ui->prompt->setText("用户名已被注册");
        ui->userName->setFocus();
        return;
    }

    QByteArray userCipherHex;
    //为不同身份制作不同的哈希值
    if(identity=="admin"){
        userCipherHex=QCryptographicHash::hash(("admin"+password).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex();
    }else if(identity=="teacher"){
        userCipherHex=QCryptographicHash::hash(("teacher"+password).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex();
    }else if(identity=="rulemaker"){
        userCipherHex=QCryptographicHash::hash(("rulemaker"+password).toLocal8Bit(),QCryptographicHash::Sha3_512).toHex();
    }else{
        ui->prompt->setText("用户身份不存在");
        ui->identity->setFocus();
        return;
    }
    // 判断用户是否已经提交过注册申请
    QFile signUpWrite("./SignUp/"+userName.trimmed()+"."+identity.trimmed());
    if(signUpWrite.exists()){
        ui->prompt->setText("用户正在注册中");
        ui->userName->setFocus();
        return;
    }
    // 都没有问题，则真正开始注册流程
    signUpWrite.open(QIODevice::WriteOnly);
    QTextStream signUpStream(&signUpWrite);
    signUpStream.setEncoding(QStringConverter::Utf8);
    signUpStream<<userCipherHex;
    ui->prompt->setText("提交注册申请成功");
}

void SignUpDialog::on_cancelButton_clicked()
{
    emit signup_panel_be_closed();
}

void SignUpDialog::on_userName_textEdited(const QString &arg1)
{
    ui->prompt->setText("");
}

void SignUpDialog::open_signup_panel(){
    this->setWindowTitle("注册确认");
    this->show();
}

void SignUpDialog::close_signup_panel(){
    this->deleteLater();
    parentWidget()->show();
}
