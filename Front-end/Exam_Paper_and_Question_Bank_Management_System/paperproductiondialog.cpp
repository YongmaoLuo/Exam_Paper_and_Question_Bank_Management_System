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
        QMessageBox::information(this,"提示","试卷列表为空！请添加题目后输出。");
        return;
    }
    QString outputPaper;
    for(int i=0;i<questionsList.count();i++){
        QStringList threeElements=questionsList.at(i).split(".");
        QString subject=threeElements.at(0);
        QString chapter=threeElements.at(1);
        QString timeStamp=threeElements.at(2);
        QFile questionFile("./Question/"+subject.trimmed()+"/"+chapter.trimmed()+"/"+timeStamp.trimmed());
        questionFile.open(QIODevice::ReadOnly);
        QTextStream questionRead(&questionFile);
        QString questionText=questionRead.readAll();
        questionFile.close();
        questionText=QString::number(i+1)+"."+questionText+"\n";
        outputPaper.append(questionText);
    }
    QFile output(paperDir.path().trimmed()+"/paper.txt");
    output.open(QIODevice::WriteOnly);
    QTextStream write(&output);
    write<<outputPaper;
    output.close();
    QMessageBox::information(this,"提示","输出试卷成功，请前往相应目录查看试卷");
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
    this->setWindowTitle("试卷制作界面");
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
