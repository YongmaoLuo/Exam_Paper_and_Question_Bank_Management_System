#include "logindialog.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[]) {
    // create cache directory for Question and Bulletin
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

    // create admin account
    QFile writeFile("./User/admin");
    writeFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream adminCStream(&writeFile);
    adminCStream.setEncoding(QStringConverter::Utf8);
    QString adminOriginalCipher=adminCStream.readAll();
    if(adminOriginalCipher.trimmed().length()==0){ // admin password does not exist
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
