#include "admindialog.h"
#include "ui_admindialog.h"
#include <QFile>
#include <QDir>

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    applicantsDir.setPath("./SignUp");
    usersDir.setPath("./User");

    connect(ui->applicationlistWidget,SIGNAL(itemSelectionChanged()),SLOT(set_application_button_enable()));

    // 初始时所有按钮均处于不可用状态，防止误触
    ui->agreeButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->rejectButton->setEnabled(false);

    read_applicants(AdminDialog::applicantsDir);
    read_users(AdminDialog::usersDir);
}

void AdminDialog::read_users(QDir usersDir){
    ui->userListWidget->clear();
    usersDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    usersDir.setSorting(QDir::Name);
    // 读取系统用户,并将它们放在界面中
    QStringList userList=usersDir.entryList();
    ui->userListWidget->addItems(userList);
    ui->deleteButton->setEnabled(false);
}

void AdminDialog::read_applicants(QDir applicantsDir){
    ui->applicationlistWidget->clear();
    // 读取申请注册的人
    applicantsDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    applicantsDir.setSorting(QDir::Size | QDir::Reversed);
    QStringList applicantList=applicantsDir.entryList();
    ui->applicationlistWidget->addItems(applicantList);
    ui->agreeButton->setEnabled(false);
    ui->rejectButton->setEnabled(false);
}

void AdminDialog::set_application_button_enable(){
    ui->agreeButton->setEnabled(true);
    ui->rejectButton->setEnabled(true);
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::on_exitButton_clicked()
{
    emit admin_panel_be_closed();
}

void AdminDialog::on_agreeButton_clicked()
{
    agree_applicant(ui->applicationlistWidget->currentItem()->text().trimmed());
}

void AdminDialog::agree_applicant(QString applicantName){
    QStringList nameAndIdentity=applicantName.split(".");
    QFile agreeUser("./SignUp/"+applicantName);
    bool ok=agreeUser.copy("./User/"+nameAndIdentity.at(0));
    if(!ok){
        qDebug("Copy file to dir user failed!");
    }else{
        ok=agreeUser.remove();
        if(!ok){
            qDebug("failed to remove the application information.");
        }
    }
    ui->agreeButton->setEnabled(false);
    ui->rejectButton->setEnabled(false);
    read_users(AdminDialog::usersDir);
    read_applicants(AdminDialog::applicantsDir);
}

void AdminDialog::on_rejectButton_clicked()
{
    reject_applicant(ui->applicationlistWidget->currentItem()->text().trimmed());
}

void AdminDialog::reject_applicant(QString applicantName){
    QFile agreeUser("./SignUp/"+applicantName);
    if(!agreeUser.exists()){
        qDebug("agree applicant to become a User failed!\n");
    }

    bool ok=agreeUser.remove();
    if(!ok){
        qDebug("failed to remove the application information.");
    }
    read_applicants(AdminDialog::applicantsDir);
}

void AdminDialog::on_deleteButton_clicked()
{
    delete_user(ui->userListWidget->currentItem()->text().trimmed());
}

void AdminDialog::delete_user(QString userName){
    QFile agreeUser("./User/"+userName);
    if(!agreeUser.exists()){
        qDebug("agree applicant to become a member failed!\n");
    }

    bool ok=agreeUser.remove();
    if(!ok){
        qDebug("failed to remove the application information.");
    }
    read_users(AdminDialog::usersDir);
}
void AdminDialog::on_userListWidget_itemSelectionChanged()
{
    ui->deleteButton->setEnabled(true);
}

void AdminDialog::open_admin_panel(){
    this->setWindowTitle("管理界面");
    this->show();
}

void AdminDialog::close_admin_panel(){
    this->deleteLater();
    parentWidget()->show();
}
