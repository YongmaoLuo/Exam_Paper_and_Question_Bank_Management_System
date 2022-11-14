#ifndef OWNINTERFACE
#define OWNINTERFACE

#include <QString>
#include <QDir>
#include <QDialog>
#include "tcpclientsocket.h"
#include <nlohmann/json.hpp>
#include <unistd.h>
#define FMT_HEADER_ONLY
#include "fmt/format.h"
using json=nlohmann::json;

class Login{// login panel
protected:
    virtual void submit_login(QString userName,QString password)=0;// submit login request
public:
    virtual void open_login_panel()=0;// open login panel
};

class Admin{// system admin
protected:
    virtual void read_users()=0; // read all users in the system
    virtual void delete_user(QString userName)=0; // delete users in the system
    virtual void register_user(QString userName,QString password)=0; // create a new user in the system
public:
    virtual void open_admin_panel()=0;// do something before opening an admin panel
    virtual void close_admin_panel()=0;// slot for closing admin panel
};

class RuleMaker{ // rulemaker
protected:
    virtual void create_bulletin(QString teacherName, QString timeStamp)=0;// create bulletin
    virtual void delete_bulletin(QString fileName)=0;// delete selected bulletin
    virtual void load_bulletin(QString fileName)=0;// load the text of a selected bulletin into the text editor
    virtual void write_bulletin(QString fileName,QString bulletinText)=0;// submit the modified text
    virtual void read_bulletins()=0;// read the names of the bulletins and show them
public:
    virtual void open_rulemaker_panel()=0;// open the rulemaker panel
    virtual void close_rulemaker_panel()=0;// close the rulemaker panel
};

class QuestionManagement{// question management (teacher)
protected:
    QDir libraryDir;
    virtual void read_subjects()=0;// read all subjects into the subject area
    virtual void read_chapters(QString subject)=0;// read all chapters for a specific subject
    virtual void read_questions(QString subject,QString chapter)=0;// read all questions for a chapter
    virtual void add_subject(QString subject)=0;// add a new subject
    virtual void add_chapter(QString subject,QString chapter)=0;// add a new chapter
    virtual void add_question(QString subject,QString chapter,QString questionName)=0;// add a new question file
    virtual void delete_subject(QString subject)=0;// delete subject
    virtual void delete_chapter(QString subject,QString chapter)=0;// delete chapter of a subject
    virtual void delete_question(QString subject,QString chapter,QString questionName)=0;// delete one question
    virtual void load_question(QString subject,QString chapter,QString timeStamp)=0;// load the question text to the editor
    virtual void write_question(QString subject,QString chapter,QString timeStamp,QString questionText)=0;// submit question text after editing
public:
    virtual void open_question_management_panel()=0;// open the window
    virtual void close_question_management_panel()=0;// close the window
};

class PaperProduction{// paper generation
protected:
    QStringList questionsList;// 储存试卷题目的列表
    virtual void delete_question(QString questionName)=0;// 在试卷中删除某题目
    virtual void output_paper(QDir paperDir,QStringList questionsList)=0;// 输出试卷
    virtual void read_questions(QStringList questionsList)=0;// 读取目前试卷题目列表中的所有题目，并且呈现出来
public:
    virtual void add_question(QString subject,QString chapter,QString timeStamp)=0;// 向试卷中添加某题目
    virtual void open_paper_production_panel()=0;// 打开试卷制作窗口
    virtual void close_paper_production_panel()=0;// 关闭试卷制作窗口
};

#endif
