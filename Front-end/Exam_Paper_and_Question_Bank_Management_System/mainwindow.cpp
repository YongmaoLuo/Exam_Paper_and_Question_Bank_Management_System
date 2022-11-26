#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rulemakerdialog.h"
#include "paperproductiondialog.h"
#include <QInputDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent, std::unique_ptr<TCPClientSocket> client)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->client=std::move(client);
    ui->subjectDeleteButton->setEnabled(false);
    ui->chapterDeleteButton->setEnabled(false);
    ui->chapterCreateButton->setEnabled(false);
    ui->questionCreateButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
    ui->addPaperButton->setEnabled(false);
    ui->storeButton->setEnabled(false);
    get_subjects();

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::get_subjects() {
    ui->subjectListWidget->clear();
    json sendPacket=R"({"command":"get subjects"})"_json;
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get bulletins command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive bulletin list failed");
    }
    int iter=0;
    QList<QString> subjectList;
    if(recvPacket["code"]==200){
        iter=recvPacket["counts"];
        for(int i=0;i<iter;i++){
            if(client->receive(recvPacket)==-1){
                QMessageBox::warning(this,"warning","receive subjects' names failed");
                return;
            }
            QString subjectName=QString::fromUtf8(std::string(recvPacket["subject name"]).c_str());
            subjectList.append(subjectName);
        }
    }else{
        QMessageBox::warning(this,"warning","undefined message from server");
        return;
    }
    ui->subjectListWidget->addItems(subjectList);
    ui->subjectDeleteButton->setEnabled(false);
}

void MainWindow::get_chapters(QString subject){
    ui->chapterListWidget->clear();
    json sendPacket=R"({"command":"get chapters"})"_json;
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get bulletins command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive bulletin list failed");
    }
    int iter=0;
    QList<QString> chapterList;
    if(recvPacket["code"]==200){
        iter=recvPacket["counts"];
        for(int i=0;i<iter;i++){
            if(client->receive(recvPacket)==-1){
                QMessageBox::warning(this,"warning","receive chapters' names failed");
                return;
            }
            QString chapterName=QString::fromUtf8(std::string(recvPacket["chapter name"]).c_str());
            chapterList.append(chapterName);
        }
    }else{
        QMessageBox::warning(this,"warning","undefined message from server");
        return;
    }
    ui->chapterListWidget->addItems(chapterList);
    ui->chapterDeleteButton->setEnabled(false);
}

void MainWindow::get_questions(QString subject,QString chapter){
    ui->questionListWidget->clear();
    json sendPacket=R"({"command":"get questions"})"_json;
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get bulletins command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive bulletin list failed");
    }
    int iter=0;
    QList<QString> questionList;
    if(recvPacket["code"]==200){
        iter=recvPacket["counts"];
        for(int i=0;i<iter;i++){
            if(client->receive(recvPacket)==-1){
                QMessageBox::warning(this,"warning","receive questions' names failed");
                return;
            }
            QString questionName=QString::fromUtf8(std::string(recvPacket["question name"]).c_str());
            questionList.append(questionName);
        }
    }else{
        QMessageBox::warning(this,"warning","undefined message from server");
        return;
    }
    ui->questionListWidget->addItems(questionList);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::add_subject(QString subject){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"add subject\",\"subject name\":\"{}\"}}",
                                            subject.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send add subject command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive server response failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","add subject unsuccessful from the server");
        return;
    }
    get_subjects();
    ui->chapterDeleteButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::add_chapter(QString subject,QString chapter){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"add chapter\",\"subject name\":\"{}\",\"chapter name\":\"{}\"}}",
                                            subject.toStdString(),chapter.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send add chapter command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive server response failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","add chapter unsuccessful from the server");
        return;
    }
    get_chapters(subject);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::add_question(QString subject,QString chapter,QString questionName){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"add question\",\"subject name\":\"{}\",\"chapter name\":\"{}\",\"question name\":\"{}\"}}",
                                            subject.toStdString(),chapter.toStdString(),questionName.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send add questions command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive server response failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","add question unsuccessful from the server");
        return;
    }
    get_questions(subject,chapter);
}

void MainWindow::delete_subject(QString subject){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"delete subject\",\"subject name\":\"{}\"}}",
                                            subject.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send delete subject command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive server response failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","delete subject unsuccessful from the server");
        return;
    }
    get_subjects();
    ui->chapterListWidget->clear();
    ui->questionListWidget->clear();
    ui->chapterDeleteButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::delete_chapter(QString subject,QString chapter){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"delete chapter\",\"subject name\":\"{}\",\"chapter name\":\"{}\"}}",
                                            subject.toStdString(),chapter.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get users command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive user list failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","delete chapter unsuccessful from the server");
        return;
    }
    get_chapters(subject);
    ui->questionListWidget->clear();
    ui->questionDeleteButton->setEnabled(false);
}

void MainWindow::delete_question(QString subject,QString chapter,QString questionName){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"delete question\",\"subject name\":\"{}\",\"chapter name\":\"{}\",\"question name\":\"{}\"}}",
                                            subject.toStdString(),chapter.toStdString(),questionName.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get users command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive user list failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","delete question unsuccessful from the server");
        return;
    }
    get_questions(subject,chapter);
}

void MainWindow::read_question(QString subject,QString chapter,QString questionName){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"read question\",\"subject name\":\"{}\",\"chapter name\":\"{}\",\"question name\":\"{}\"}}",
                                            subject.toStdString(),chapter.toStdString(),questionName.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send get users command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive server response failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","read question unsuccessful from the server");
        return;
    }
    this->tempQuestionName=questionName;
    this->tempQuestionText=QString::fromUtf8(std::string(recvPacket["question text"]).c_str());
    ui->textEdit->setText(this->tempQuestionText);
}
void MainWindow::write_question(QString subject,QString chapter,QString questionName,QString questionText){
    json sendPacket=json::parse(fmt::format("{{\"command\":\"submit question\",\"subject name\":\"{}\",\"chapter name\":\"{}\","
                                            "\"question name\":\"{}\",\"question text\":\"{}\"}}",
                                            subject.toStdString(),chapter.toStdString(),questionName.toStdString(),questionText.toStdString()));
    if(client->sendToServer(sendPacket)==-1){
        QMessageBox::warning(this,"warning","send write question command failed");
    }
    json recvPacket;
    if(client->receive(recvPacket)==-1){
        QMessageBox::warning(this,"warning","receive server response failed");
    }
    if(recvPacket["code"]!=200){
        QMessageBox::warning(this,"warning","write question unsuccessful from the server");
        return;
    }
}
void MainWindow::close_question_management_panel(){
    this->deleteLater();
    parentWidget()->show();
}

void MainWindow::open_question_management_panel(){
    this->setWindowTitle("question management window");
    this->show();
}

void MainWindow::on_subjectDeleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::information(this,"confirmation","Are you sure you want to delete all contents under the subject?");
    if(reply==QMessageBox::Cancel){
        return;
    }
    delete_subject(ui->subjectListWidget->currentItem()->text().trimmed());
}

void MainWindow::on_subjectCreateButton_clicked()
{
    QString text = QInputDialog::getText(this, "Get the name of the subject","please enter the subject name", QLineEdit::Normal,0);
    add_subject(text);
}

void MainWindow::on_chapterDeleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::information(this,"confirmation","Are you sure you want to delete all contents under the chapter?");
    if(reply==QMessageBox::Cancel){
        return;
    }
    delete_chapter(ui->subjectListWidget->currentItem()->text().trimmed(),ui->chapterListWidget->currentItem()->text().trimmed());
}

void MainWindow::on_chapterCreateButton_clicked()
{
    QString text = QInputDialog::getText(this, "Get the name of the chapter","please enter the chapter name", QLineEdit::Normal,0);
    add_chapter(ui->subjectListWidget->currentItem()->text().trimmed(),text);
}

void MainWindow::on_storeButton_clicked()
{
    QString subject=ui->subjectListWidget->currentItem()->text().trimmed();
    QString chapter=ui->chapterListWidget->currentItem()->text().trimmed();
    QString questionName=ui->questionListWidget->currentItem()->text().trimmed();
    QString questionText=ui->textEdit->toPlainText().trimmed();
    write_question(subject,chapter,questionName,questionText);
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
    this->tempSubject=item->text().trimmed();
    get_chapters(this->tempSubject);

    ui->chapterCreateButton->setEnabled(true);
    ui->chapterDeleteButton->setEnabled(false);
    ui->questionDeleteButton->setEnabled(false);
    ui->addPaperButton->setEnabled(false);
}

void MainWindow::on_chapterListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    this->tempChapter=item->text().trimmed();
    get_questions(this->tempSubject,this->tempChapter);
    ui->questionCreateButton->setEnabled(true);
    ui->questionDeleteButton->setEnabled(false);
    ui->addPaperButton->setEnabled(false);
}

void MainWindow::on_questionListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->storeButton->setEnabled(true);
    this->tempQuestionName=item->text().trimmed();
    read_question(this->tempSubject,this->tempChapter,this->tempQuestionName);
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
