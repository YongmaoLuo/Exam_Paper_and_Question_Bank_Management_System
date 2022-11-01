#include "rulemakerdialog.h"
#include "ui_rulemakerdialog.h"
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

RuleMakerDialog::RuleMakerDialog(QWidget *parent) :
    QDialog(parent),ui(new Ui::RuleMakerDialog)
{
    ui->setupUi(this);
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

void RuleMakerDialog::read_bulletins(QDir bulletinDir){
    ui->bulletinListWidget->clear();
    if(!bulletinDir.exists()){
        bulletinDir.mkpath(".");
    }
    bulletinDir.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
    bulletinDir.setSorting(QDir::Name);
    QStringList bulletinList=bulletinDir.entryList();
    ui->bulletinListWidget->addItems(bulletinList);
    ui->deleteButton->setEnabled(false);
}

void RuleMakerDialog::close_rulemaker_panel(){
    this->deleteLater();
    parentWidget()->show();
}

void RuleMakerDialog::open_rulemaker_panel(){
    this->setWindowTitle("试卷规则制定");
    this->show();
}

void RuleMakerDialog::on_bulletinListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->submitButton->setEnabled(true);
    load_bulletin(rulemakerDir,item->text());
}

void RuleMakerDialog::on_deleteButton_clicked()
{
    delete_bulletin(rulemakerDir,ui->bulletinListWidget->currentItem()->text());
}

void RuleMakerDialog::on_createButton_clicked()
{
    QDateTime time=QDateTime::currentDateTime();
    QString timeStamp=time.toString("yyyy-MM-dd_hh-mm-ss");
    create_bulletin(rulemakerDir,timeStamp);
}

void RuleMakerDialog::create_bulletin(QDir rulemakerDir, QString timeStamp){
    QFile writeBulletin(rulemakerDir.path().trimmed()+"/"+timeStamp);
    if(writeBulletin.exists()){
        return;
    }
    writeBulletin.open(QIODevice::WriteOnly);
    QTextStream write(&writeBulletin);
    write<<"";
    writeBulletin.close();
    read_bulletins(this->rulemakerDir);
}
