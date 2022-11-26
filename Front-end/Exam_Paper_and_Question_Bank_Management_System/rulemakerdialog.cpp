#include "rulemakerdialog.h"
#include "ui_rulemakerdialog.h"
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

std::string escapeJsonString(std::string input){
    for(int i=0;;i++){
        if(i>=input.length())
            break;
        if(input[i]=='\n'){
            input.erase(i,1);
            input.insert(i,"\\n");
            i++;
        }else if(input[i]=='\\'){
            input.insert(i,"\\");
            i++;
    }
    }
    return input;
}

RuleMakerDialog::RuleMakerDialog(QWidget *parent, std::unique_ptr<TCPClientSocket> client) :
    QDialog(parent),ui(new Ui::RuleMakerDialog)
{
    ui->setupUi(this);
    this->client=std::move(client);
    ui->deleteButton->setEnabled(false);
    ui->submitButton->setEnabled(false);
    ui->createButton->setEnabled(false);
    this->tempBulletinName="";
    this->tempBulletinText="";
}

RuleMakerDialog::~RuleMakerDialog(){
    delete ui;
}

void RuleMakerDialog::close_rulemaker_panel(){
    this->deleteLater();
    parentWidget()->show();
}

void RuleMakerDialog::open_rulemaker_panel(){
    this->setWindowTitle("window for rule makers");
    this->get_bulletins();
    this->get_teachers();
    this->show();
}

void RuleMakerDialog::on_bulletinListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //this->tempBulletinText=ui->bulletinTextEdit->toPlainText().trimmed();
    std::cout<<"double click bulletin list"<<std::endl;
    if(this->tempBulletinName!=""&&item->text().compare(this->tempBulletinName)!=0){
        replace_current_bulletin_file(item->text());
    }
    if(this->tempBulletinName=="")
        this->tempBulletinName=item->text();
    std::cout<<"replace temp bulletin name successfully"<<std::endl;
    read_bulletin(this->tempBulletinName);
    ui->bulletinTextEdit->setText(this->tempBulletinText);
    ui->submitButton->setEnabled(true);
    ui->bulletinListWidget->setCurrentItem(item);
}

void RuleMakerDialog::on_deleteButton_clicked()
{
    delete_bulletin(ui->bulletinListWidget->currentItem()->text());
    get_bulletins();
}

void RuleMakerDialog::on_createButton_clicked()
{
    QDateTime time=QDateTime::currentDateTime();
    QString timeStamp=time.toString("yyyy-MM-dd_hh-mm-ss");
    QString teacherName=ui->teacherListWidget->currentItem()->text();
    create_bulletin(teacherName,timeStamp);
    ui->createButton->setEnabled(false);
    ui->teacherListWidget->clearSelection();
    ui->submitButton->setEnabled(true);
}

void RuleMakerDialog::on_submitButton_clicked(){
    write_bulletin(this->tempBulletinName,ui->bulletinTextEdit->toPlainText().trimmed());
    ui->submitButton->setEnabled(false);
    ui->bulletinTextEdit->setText("");
}

void RuleMakerDialog::on_bulletinListWidget_itemSelectionChanged(){
    ui->deleteButton->setEnabled(true);
}

void RuleMakerDialog::on_teacherListWidget_itemSelectionChanged(){
    if(ui->teacherListWidget->selectedItems().size()!=0){
        ui->createButton->setEnabled(true);
    }
}

void RuleMakerDialog::on_exitButton_clicked(){
    emit rulemaker_panel_be_closed();
}

void RuleMakerDialog::delete_bulletin(QString bulletinName){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"delete bulletin\",\"bulletin name\":\"{}\"}}",bulletinName.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get users command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive user list failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","delete unsuccessful from the server");
        return;
    }
}

void RuleMakerDialog::read_bulletin(QString bulletinName){
    std::cout<<"begin reading bulletin..."<<std::endl;
    json sendPacket=json::parse(fmt::format("{{\"command\":\"read bulletin\",\"bulletin name\":\"{}\"}}",bulletinName.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get users command failed");
        return;
    }
    std::cout<<"send to server successfully"<<std::endl;
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","get feedback from server failed");
        return;
    }
    std::cout<<"receive from server successfully"<<std::endl;
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","read unsuccessful from the server");
        get_bulletins();
        get_teachers();
        return;
    }
    this->tempBulletinName=bulletinName;
    this->tempBulletinText=QString::fromUtf8(std::string(recvPacket["bulletin text"]).c_str());
}

void RuleMakerDialog::write_bulletin(QString bulletinName,QString bulletinText){
    std::cout<<"begin writing bulletin..."<<std::endl;
    std::string afterEscape=escapeJsonString(bulletinText.toStdString());
    std::cout<<"escape successfully"<<std::endl;
    std::istringstream iss{bulletinName.toStdString()};
    std::string teacherName;
    std::getline(iss,teacherName,'+');
    std::cout<<"teacher name is: "<<teacherName<<std::endl;
    json sendPacket=json::parse(fmt::format("{{\"command\":\"write bulletin\",\"bulletin name\":\"{}\",\"bulletin text\":\"{}\",\"teacher name\":\"{}\"}}",
                                            bulletinName.toStdString(),afterEscape,teacherName));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send write bulletin command failed");
        std::cout<<"send write bulletin command failed"<<std::endl;
        return;
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive server response failed");
        return;
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","submit unsuccessful from the server");
        return;
    }
}

void RuleMakerDialog::get_bulletins(){
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

void RuleMakerDialog::get_teachers(){
    ui->teacherListWidget->clear();
    // read bulletins from the back-end and store the names in list
    json sendPacket=R"({"command":"get teachers"})"_json;
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get bulletins command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive bulletin list failed");
    }
    int iter=0;
    QList<QString> teacherList;
    if(recvPacket["code"]==200){
        iter=recvPacket["counts"];
        for(int i=0;i<iter;i++){
            if(client->receive(recvPacket)==-1){
                QMessageBox::warning(this,"warning","receive teacher names failed");
                return;
            }
            QString teacherName=QString::fromUtf8(std::string(recvPacket["username"]).c_str());
            teacherList.append(teacherName);
        }
    }else{
        QMessageBox::warning(this,"warning","undefined message from server");
        return;
    }
    ui->teacherListWidget->addItems(teacherList);
    ui->deleteButton->setEnabled(false);
}

void RuleMakerDialog::create_bulletin(QString teacherName,QString timeStamp){
    this->tempBulletinName=teacherName+"+"+timeStamp;
    this->tempBulletinText=NULL;
    ui->bulletinListWidget->addItem(this->tempBulletinName);
    ui->bulletinListWidget->setCurrentItem(ui->bulletinListWidget->findItems(this->tempBulletinName,Qt::MatchExactly)[0]);
    ui->bulletinTextEdit->setFocus();
}

void RuleMakerDialog::replace_current_bulletin_file(QString bulletinName){
    if(ui->bulletinTextEdit->toPlainText().trimmed().compare("")!=0){
        this->tempBulletinText=ui->bulletinTextEdit->toPlainText().trimmed();
        this->write_bulletin(this->tempBulletinName,this->tempBulletinText);
    }
    ui->submitButton->setEnabled(false);
    this->tempBulletinName=bulletinName;
}
