#include "rulemakerdialog.h"
#include "ui_rulemakerdialog.h"
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

RuleMakerDialog::RuleMakerDialog(QWidget *parent, TCPClientSocket *client) :
    QDialog(parent),ui(new Ui::RuleMakerDialog)
{
    ui->setupUi(this);
    this->client=client;
    ui->deleteButton->setEnabled(false);
    ui->submitButton->setEnabled(false);
}

RuleMakerDialog::~RuleMakerDialog(){
    delete ui;
}

void RuleMakerDialog::on_submitButton_clicked(){
    write_bulletin(this->rulemakerDir,ui->bulletinListWidget->currentItem()->text(),ui->bulletinTextEdit->toPlainText().trimmed());
    ui->submitButton->setEnabled(false);
    ui->bulletinTextEdit->setText("");
}

void RuleMakerDialog::on_bulletinListWidget_itemSelectionChanged(){
    ui->deleteButton->setEnabled(true);
}

void RuleMakerDialog::on_exitButton_clicked(){
    emit rulemaker_panel_be_closed();
}

void RuleMakerDialog::delete_bulletin(QDir rulemakerDir,QString timeStamp){
    QFile remove(rulemakerDir.path().trimmed()+"/"+timeStamp.trimmed());
    remove.remove();
    read_bulletins(this->rulemakerDir);
}
void RuleMakerDialog::load_bulletin(QDir rulemakerDir,QString timeStamp){
    QFile load(rulemakerDir.path().trimmed()+"/"+timeStamp.trimmed());
    load.open(QIODevice::ReadOnly);
    QTextStream bulletinText(&load);
    QString text=bulletinText.readAll().trimmed();
    ui->bulletinTextEdit->setText(text);
    load.close();
}

void RuleMakerDialog::write_bulletin(QDir rulemakerDir, QString timeStamp,QString bulletinText){
    QFile writeBulletin(rulemakerDir.path().trimmed()+"/"+timeStamp.trimmed());
    writeBulletin.open(QIODevice::WriteOnly);
    QTextStream writeText(&writeBulletin);
    writeText<< bulletinText;
}

void RuleMakerDialog::read_bulletins(){
    ui->bulletinListWidget->clear();
    // read bulletins from the back-end and store the names in list
    json sendPacket=R"({"command":"get bulletins"})"_json;
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get bulletins command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive bulletin list failed");
    }
    int iter=0;
    QList<QString> bulletinList;
    if(recvPacket["code"]==200){
        iter=recvPacket["counts"];
        for(int i=0;i<iter;i++){
            if(client->receive(recvPacket)==-1){
                QMessageBox::warning(this,"warning","receive user names failed");
                return;
            }
            QString bulletinName=QString::fromUtf8(std::string(recvPacket["bulletin name"]).c_str());
            bulletinList.append(bulletinName);
        }
    }else{
        QMessageBox::warning(this,"warning","undefined message from server");
        return;
    }
    ui->bulletinListWidget->addItems(bulletinList);
    ui->deleteButton->setEnabled(false);
}

void RuleMakerDialog::close_rulemaker_panel(){
    this->deleteLater();
    delete this->client;
    parentWidget()->show();
}

void RuleMakerDialog::open_rulemaker_panel(){
    this->setWindowTitle("window for rule makers");
    this->read_bulletins();
    this->show();
}

void RuleMakerDialog::on_bulletinListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->submitButton->setEnabled(true);
    load_bulletin(item->text());
}

void RuleMakerDialog::on_deleteButton_clicked()
{
    delete_bulletin(ui->bulletinListWidget->currentItem()->text());
}

void RuleMakerDialog::on_createButton_clicked()
{
    QDateTime time=QDateTime::currentDateTime();
    QString timeStamp=time.toString("yyyy-MM-dd_hh-mm-ss");
    QString teacherName=ui->teacherListWidget->currentItem()->text();
    create_bulletin(teacherName,timeStamp);
}

void RuleMakerDialog::create_bulletin(QString teacherName,QString timeStamp){
    this->tempBulletinName=teacherName+timeStamp;
    this->tempBulletinText="";
    ui->bulletinListWidget->addItem(this->tempBulletinName);
    ui->bulletinTextEdit->setFocus();
}
