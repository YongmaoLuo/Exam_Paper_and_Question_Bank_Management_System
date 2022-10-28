#include "mainwindow.h"
#include "logindialog.h"
#include "admindialog.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[]) {
    // 创建必要的User,Question,SignUp和Bulletin目录
    QDir dir("./User");
    if(!dir.exists()){
        dir.mkpath(".");
    }
    dir.setPath("./Question");
    if(!dir.exists()){
        dir.mkpath(".");
    }
    dir.setPath("./SignUp");
    if(!dir.exists()){
        dir.mkpath(".");
    }
    dir.setPath("./Bulletin");
    if(!dir.exists()){
        dir.mkpath(".");
    }

    // 创建管理员账户
    QFile writeFile("./User/admin");
    writeFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream adminCStream(&writeFile);
    adminCStream.setCodec("UTF-8");
    QString adminOriginalCipher=adminCStream.readAll();
    if(adminOriginalCipher.trimmed().length()==0){ // 说明admin的密码原本不存在，需要重置密码。
        QString initial="admin";
        QByteArray adminCipher=QCryptographicHash::hash(("admin"+initial).toLocal8Bit(),QCryptographicHash::Sha3_512);
        adminCStream<<adminCipher.toHex();
        qDebug()<<adminCipher.toHex();
        fflush(stdout);
    }
    writeFile.close();

    QApplication a(argc, argv);
    LoginDialog login(nullptr);
    login.open_login_panel();

    return a.exec();
}
