#include "paperproductiondialog.h"
#include "ui_paperproductiondialog.h"
#include <QTextStream>
#include <QMessageBox>
PaperProductionDialog::PaperProductionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaperProductionDialog)
{
    ui->setupUi(this);
    ui->deleteButton->setEnabled(false);
}

PaperProductionDialog::~PaperProductionDialog()
{
    delete ui;
}

void PaperProductionDialog::delete_question(QString questionName){
    this->questionsList.removeOne(questionName.trimmed());
    read_questions(this->questionsList);
}

void PaperProductionDialog::output_paper(QDir paperDir,QStringList questionsList){
    if(questionsList.isEmpty()){
        QMessageBox::information(this,"remind","the question list is empty, please add questions to it");
        return;
    }
    json sendPacket=json::parse(fmt::format("{{\"command\":\"produce paper\",\"count\":\"{}\"}}",questionsList.count()));
//    if(client->sendToServer(sendPacket)==-1){
//        QMessageBox::warning(this,"warning","send write question command failed");
//        return;
//    }
//    json recvPacket;
//    if(client->receive(recvPacket)==-1){
//        QMessageBox::warning(this,"warning","receive server response failed");
//        return;
//    }
    QString outputPaper;
    for(int i=0;i<questionsList.count();i++){
        QStringList threeElements=questionsList.at(i).split(".");
        QString subject=threeElements.at(0);
        QString chapter=threeElements.at(1);
        QString timeStamp=threeElements.at(2);
        //QFile questionFile("./Question/"+subject.trimmed()+"/"+chapter.trimmed()+"/"+timeStamp.trimmed());
        //questionFile.open(QIODevice::ReadOnly);
        //QTextStream questionRead(&questionFile);
        //QString questionText=questionRead.readAll();
        //questionFile.close();
        //questionText=QString::number(i+1)+"."+questionText+"\n";
        //outputPaper.append(questionText);
    }
    QFile output(paperDir.path().trimmed()+"/paper.txt");
    output.open(QIODevice::WriteOnly);
    QTextStream write(&output);
    write<<outputPaper;
    output.close();
    QMessageBox::information(this,"reminder","output paper successfully, please go to the desktop to find the paper file");
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
    output_paper(QDir("."),this->questionsList);
}
