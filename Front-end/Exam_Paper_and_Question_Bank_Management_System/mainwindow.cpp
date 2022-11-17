#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rulemakerdialog.h"
#include "paperproductiondialog.h"
#include <QInputDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent, TCPClientSocket *client)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->client=client;
    ui->subjectDeleteButton->setEnabled(false);
    ui->chapterDeleteButton->setEnabled(false);
    ui->chapterCreateButton->setEnabled(false);
    ui->questionCreateButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
    ui->addPaperButton->setEnabled(false);
    ui->storeButton->setEnabled(false);

    this->libraryDir=QDir("./Question");
    read_subjects(libraryDir);

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::read_subjects(QDir libraryDir) {
    ui->subjectListWidget->clear();
    if(!libraryDir.exists()){
        libraryDir.mkpath(".");
    }
    libraryDir.setFilter(QDir::Dirs|QDir::Hidden|QDir::NoSymLinks|QDir::NoDot|QDir::NoDotDot);
    libraryDir.setSorting(QDir::Name);
    QStringList subjectsList=libraryDir.entryList();
    ui->subjectListWidget->addItems(subjectsList);
    ui->subjectDeleteButton->setEnabled(false);
}

void MainWindow::read_chapters(QString subject){
    ui->chapterListWidget->clear();
    QDir subjectDir(libraryDir.path().trimmed()+"/"+subject.trimmed());
    if(!subjectDir.exists()){
        subjectDir.mkpath(".");
    }
    subjectDir.setFilter(QDir::Dirs|QDir::Hidden|QDir::NoSymLinks|QDir::NoDot|QDir::NoDotDot);
    subjectDir.setSorting(QDir::Name);
    QStringList chaptersList=subjectDir.entryList();
    ui->chapterListWidget->addItems(chaptersList);
    ui->subjectDeleteButton->setEnabled(false);
}

void MainWindow::read_questions(QString subject,QString chapter){
    ui->questionListWidget->clear();
    QDir questionDir(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed());
    if(!questionDir.exists()){
        questionDir.mkpath(".");
    }
    questionDir.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
    questionDir.setSorting(QDir::Name);
    QStringList chaptersList=questionDir.entryList();
    ui->questionListWidget->addItems(chaptersList);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::add_subject(QString subject){
    QDir subjectDir(libraryDir.path().trimmed()+"/"+subject.trimmed());
    if(subjectDir.exists()){
        return;
    }
    subjectDir.mkpath(".");
    read_subjects(this->libraryDir);
    ui->chapterDeleteButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::add_chapter(QString subject,QString chapter){
    QDir chapterDir(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed());
    if(chapterDir.exists()){
        return;
    }
    chapterDir.mkpath(".");
    read_chapters(subject);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::add_question(QString subject,QString chapter,QString timeStamp){
    QFile questionFile(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed()+"/"+timeStamp.trimmed());
    if(questionFile.exists()){
        return;
    }
    questionFile.open(QIODevice::WriteOnly);
    QTextStream write(&questionFile);
    write<<"";
    questionFile.close();
    read_questions(subject,chapter);
}

void MainWindow::delete_subject(QString subject){
    QDir subjectDir(libraryDir.path().trimmed()+"/"+subject.trimmed());
    subjectDir.setFilter(QDir::Dirs|QDir::Hidden|QDir::NoSymLinks|QDir::NoDot|QDir::NoDotDot);
    subjectDir.setSorting(QDir::Name);
    QStringList chaptersList=subjectDir.entryList();
    for(int i=0;i<chaptersList.count();i++){
        recursive_delete_chapter(subject,chaptersList.at(i));
    }
    subjectDir.rmdir(".");
    read_subjects(this->libraryDir);
    ui->chapterListWidget->clear();
    ui->questionListWidget->clear();
    ui->chapterDeleteButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::recursive_delete_chapter(QString subject,QString chapter){
    QDir chapterDir(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed());
    chapterDir.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
    chapterDir.setSorting(QDir::Name);
    QStringList questionsList=chapterDir.entryList();
    for(int i=0;i<questionsList.count();i++){
        recursive_delete_question(subject,chapter,questionsList.at(i));
    }
    chapterDir.rmdir(".");
}

void MainWindow::recursive_delete_question(QString subject,QString chapter,QString timeStamp){
    QFile questionFile(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed()+"/"+timeStamp.trimmed());
    questionFile.remove();
}

void MainWindow::delete_chapter(QString subject,QString chapter){
    QDir chapterDir(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed());
    chapterDir.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
    chapterDir.setSorting(QDir::Name);
    QStringList questionsList=chapterDir.entryList();
    for(int i=0;i<questionsList.count();i++){
        recursive_delete_question(subject,chapter,questionsList.at(i));
    }
    chapterDir.rmdir(".");
    read_chapters(subject);
    ui->questionListWidget->clear();
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::delete_question(QString subject,QString chapter,QString timeStamp){
    QFile questionFile(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed()+"/"+timeStamp.trimmed());
    questionFile.remove();
    read_questions(subject,chapter);
}

void MainWindow::load_question(QString subject,QString chapter,QString timeStamp){
    QFile questionFile(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed()+"/"+timeStamp.trimmed());
    questionFile.open(QIODevice::ReadOnly);
    QTextStream readQuestion(&questionFile);
    readQuestion.setEncoding(QStringConverter::Utf8);
    QString questionText=readQuestion.readAll();
    questionFile.close();
    ui->textEdit->setText(questionText.trimmed());
}
void MainWindow::write_question(QString subject,QString chapter,QString timeStamp,QString questionText){
    QFile questionFile(libraryDir.path().trimmed()+"/"+subject.trimmed()+"/"+chapter.trimmed()+"/"+timeStamp.trimmed());
    questionFile.open(QIODevice::WriteOnly);
    QTextStream writeQuestion(&questionFile);
    writeQuestion.setEncoding(QStringConverter::Utf8);
    writeQuestion<<questionText;
}
void MainWindow::close_question_management_panel(){
    this->deleteLater();
    delete this->client;
    parentWidget()->show();
}

void MainWindow::open_question_management_panel(){
    this->setWindowTitle("题库管理界面");
    this->show();
}

void MainWindow::on_subjectDeleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::information(this,"确认提示框","是否确认删除此科目下所有内容？");
    if(reply==QMessageBox::Cancel){
        return;
    }
    delete_subject(ui->subjectListWidget->currentItem()->text().trimmed());
}

void MainWindow::on_subjectCreateButton_clicked()
{
    QString text = QInputDialog::getText(this, "科目名称获取","请输入您要创建的科目名称", QLineEdit::Normal,0);
    add_subject(text);
}

void MainWindow::on_chapterDeleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::information(this,"确认提示框","是否确认删除此章节下所有内容？");
    if(reply==QMessageBox::Cancel){
        return;
    }
    delete_chapter(ui->subjectListWidget->currentItem()->text().trimmed(),ui->chapterListWidget->currentItem()->text().trimmed());
}

void MainWindow::on_chapterCreateButton_clicked()
{
    QString text = QInputDialog::getText(this, "章节名称获取","请输入您要创建的章节名称", QLineEdit::Normal,0);
    add_chapter(ui->subjectListWidget->currentItem()->text().trimmed(),text);
}

void MainWindow::on_storeButton_clicked()
{
    QString subject=ui->subjectListWidget->currentItem()->text().trimmed();
    QString chapter=ui->chapterListWidget->currentItem()->text().trimmed();
    QString timeStamp=ui->questionListWidget->currentItem()->text().trimmed();
    QString questionText=ui->textEdit->toPlainText().trimmed();
    write_question(subject,chapter,timeStamp,questionText);
    ui->textEdit->setText("");
    ui->storeButton->setEnabled(false);
}



void MainWindow::on_questionDeleteButton_clicked()
{
    QString subject=ui->subjectListWidget->currentItem()->text().trimmed();
    QString chapter=ui->chapterListWidget->currentItem()->text().trimmed();
    QString timeStamp=ui->questionListWidget->currentItem()->text().trimmed();
    delete_question(subject,chapter,timeStamp);
}

void MainWindow::on_questionCreateButton_clicked()
{
    QString subject=ui->subjectListWidget->currentItem()->text().trimmed();
    QString chapter=ui->chapterListWidget->currentItem()->text().trimmed();
    QString timeStamp=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    add_question(subject,chapter,timeStamp);
}

void MainWindow::on_subjectListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    read_chapters(item->text().trimmed());
    ui->chapterCreateButton->setEnabled(true);
    ui->chapterDeleteButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
    ui->addPaperButton->setEnabled(false);
}

void MainWindow::on_chapterListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString subject=ui->subjectListWidget->currentItem()->text().trimmed();
    read_questions(subject,item->text().trimmed());
    ui->questionCreateButton->setEnabled(true);
    ui->questionDeleteButton->setEnabled(false);
    ui->addPaperButton->setEnabled(false);
}

void MainWindow::on_questionListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->storeButton->setEnabled(true);
    QString subject=ui->subjectListWidget->currentItem()->text().trimmed();
    QString chapter=ui->chapterListWidget->currentItem()->text().trimmed();
    load_question(subject,chapter,item->text().trimmed());
    if(this->canMakePaper){
        ui->addPaperButton->setEnabled(true);
    }
}

void MainWindow::on_exitButton_clicked()
{
    emit teacher_panel_be_closed();
}

void MainWindow::on_subjectListWidget_itemClicked(QListWidgetItem *item)
{
    ui->chapterCreateButton->setEnabled(true);
    ui->subjectDeleteButton->setEnabled(true);
}

void MainWindow::on_chapterListWidget_itemClicked(QListWidgetItem *item)
{
    ui->questionCreateButton->setEnabled(true);
    ui->chapterDeleteButton->setEnabled(true);
}

void MainWindow::on_questionListWidget_itemClicked(QListWidgetItem *item)
{
    ui->questionDeleteButton->setEnabled(true);
    if(this->canMakePaper){
        ui->addPaperButton->setEnabled(true);
    }
}

void MainWindow::on_bulletinAction_triggered(){
    QString rulemakerName;
    rulemakerName = QInputDialog::getText(this, "试卷规则制定者名称获取","请输入您所要听从的试卷规则制定者的名称", QLineEdit::Normal,0);
    if(!QDir("./Bulletin/"+rulemakerName.trimmed()).exists()){
        QMessageBox::information(this,"提示","此试卷规则制定者用户不存在");
        return;
    }
    QString identityString="teacher";
    rulemakerPanel=new RuleMakerDialog(this);
    connect(rulemakerPanel,&RuleMakerDialog::rulemaker_panel_be_closed,this,&MainWindow::receive_rulemaker_panel_closure);
    connect(this,&MainWindow::teacher_close_rulemaker,rulemakerPanel,&RuleMakerDialog::close_rulemaker_panel);
    rulemakerPanel->open_rulemaker_panel();
}

void MainWindow::on_makePaperAction_triggered(){
    this->canMakePaper=true;
    if(paperPanel==nullptr){
        paperPanel=new PaperProductionDialog(this);
        connect(paperPanel,&PaperProductionDialog::paper_production_panel_be_closed,this,&MainWindow::receive_paper_production_panel_closure);
        connect(this,&MainWindow::teacher_close_paper_production,paperPanel,&PaperProductionDialog::close_paper_production_panel);
        connect(this,&MainWindow::add_question_to_paper,paperPanel,&PaperProductionDialog::add_question);
    }
    paperPanel->show();
}

void MainWindow::receive_rulemaker_panel_closure(){
    rulemakerPanel=nullptr;
    emit teacher_close_rulemaker();
}

void MainWindow::on_addPaperButton_clicked()
{
    QString subject=ui->subjectListWidget->currentItem()->text().trimmed();
    QString chapter=ui->chapterListWidget->currentItem()->text().trimmed();
    QString timeStamp=ui->questionListWidget->currentItem()->text().trimmed();
    emit add_question_to_paper(subject,chapter,timeStamp);
}

void MainWindow::receive_paper_production_panel_closure(){
    paperPanel=nullptr;
    ui->addPaperButton->setEnabled(false);
    emit teacher_close_paper_production();
}
