#include "paperproductiondialog.h"
#include "ui_paperproductiondialog.h"
#include <QTextStream>
#include <QMessageBox>
PaperProductionDialog::PaperProductionDialog(QWidget *parent,std::shared_ptr<TCPClientSocket> client) :
    QDialog(parent), ui(new Ui::PaperProductionDialog)
{
    ui->setupUi(this);
    ui->deleteButton->setEnabled(false);
    this->client = client;
}

PaperProductionDialog::~PaperProductionDialog()
{
    delete ui;
}

void PaperProductionDialog::delete_question(QString questionName){
    this->questionsList.removeOne(questionName.trimmed());
    read_questions(this->questionsList);
}

void PaperProductionDialog::output_paper(QString pathName,QStringList questionsList){
    if(questionsList.isEmpty()){
        QMessageBox::information(this,"remind","the question list is empty, please add questions to it");
        return;
    }

    QFile output("paper.txt");
    if(!QDir::setCurrent(pathName)){
        QMessageBox::information(this,"warning","open "+pathName+" failed");
        return;
    }
    if(!output.open(QIODevice::OpenModeFlag::ReadWrite)){
        QMessageBox::information(this,"warning",output.errorString()+" "+pathName+"/paper.txt");
        return;
    }
    QTextStream write(&output);
    for(int i=0;i<questionsList.count();i++){
        QStringList threeElements=questionsList.at(i).split(".");
        QString subject=threeElements.at(0);
        QString chapter=threeElements.at(1);
        QString questionName=threeElements.at(2);
        json sendPacket=json::parse(fmt::format("{{\"command\":\"read question\",\"subject name\":\"{}\",\"chapter name\":\"{}\",\"question name\":\"{}\"}}",
                                                subject.toStdString(),chapter.toStdString(),questionName.toStdString()));
        if(client->sendToServer(sendPacket)==-1){
            QMessageBox::warning(this,"warning","send read question command failed");
            return;
        }
        json recvPacket;
        if(client->receive(recvPacket)==-1){
            QMessageBox::warning(this,"warning","receive server response failed");
            return;
        }
        if(recvPacket["code"]!=200){
            QMessageBox::warning(this,"warning","read question unsuccessful from the server");
            return;
        }
        std::cout<<"question text: "<<recvPacket["question text"]<<std::endl;
        write<<QString::fromUtf8(std::string(recvPacket["question text"]).c_str())<<'\n';
        if(write.status()==QTextStream::WriteFailed){
            QMessageBox::warning(this,"warning","cannot write to this file");
            return;
        }
        write<<'\n';
    }
    write.flush();
    output.close();
    QMessageBox::information(this,"reminder",QString::fromUtf8(fmt::format("output paper successfully, please go to the {} to find the paper file",pathName.toStdString())));
}

void PaperProductionDialog::read_questions(QStringList questionsList){
    ui->listWidget->clear();
    ui->listWidget->addItems(questionsList);
    ui->deleteButton->setEnabled(false);
}

void PaperProductionDialog::add_question(QString subject,QString chapter,QString timeStamp){
    QString questionName=subject.trimmed()+"."+chapter.trimmed()+"."+timeStamp;
    this->questionsList.append(questionName);
    read_questions(this->questionsList);
}

void PaperProductionDialog::open_paper_production_panel(){
    this->setWindowTitle("paper generation window");
    this->show();
}

void PaperProductionDialog::close_paper_production_panel(){
    this->hide();
}

void PaperProductionDialog::on_hideButton_clicked()
{
    this->hide();
}

void PaperProductionDialog::closeEvent( QCloseEvent * event){
    emit paper_production_panel_be_closed();
}

void PaperProductionDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->deleteButton->setEnabled(true);
}

void PaperProductionDialog::on_deleteButton_clicked()
{
    delete_question(ui->listWidget->currentItem()->text().trimmed());
}

void PaperProductionDialog::on_outputButton_clicked()
{
    QString pathName=QStandardPaths::displayName(QStandardPaths::DownloadLocation);
    std::cout<<"path name: "<<pathName.toStdString()<<std::endl;
//    if(pathName.compare("Desktop")==0)
//        pathName="~/"+pathName;
#ifdef BUILD_ON_MAC
    pathName=".";
#endif
    output_paper(pathName,this->questionsList);
}
