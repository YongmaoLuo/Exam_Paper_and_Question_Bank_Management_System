#ifndef RULEMAKERDIALOG_H
#define RULEMAKERDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "ownInterface.h"

namespace Ui {
class RuleMakerDialog;
}

class RuleMakerDialog : public QDialog,public RuleMaker
{
    Q_OBJECT

public:
    explicit RuleMakerDialog(QWidget *parent = nullptr);
    ~RuleMakerDialog();
    void open_rulemaker_panel() override;

signals:
    void rulemaker_panel_be_closed();

private slots:
    void on_submitButton_clicked();
    void on_exitButton_clicked();
    void on_bulletinListWidget_itemSelectionChanged();
    void on_bulletinListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_deleteButton_clicked();
    void on_createButton_clicked();

public slots:
    void close_rulemaker_panel() override;// 关闭试卷规则制定者的界面

private:
    Ui::RuleMakerDialog *ui;
    void delete_bulletin(QDir rulemakerDir,QString timeStamp) override;// 删除系统中自己以前发布的公告
    void load_bulletin(QDir rulemakerDir,QString timeStamp) override;// 加载选中的某个公告到编辑板
    void write_bulletin(QDir rulemakerDir,QString timeStamp,QString bulletinText) override;// 修改系统中存在的公告
    void read_bulletins(QDir bulletinDir) override;// 读取自己在系统中的所有的公告
    void create_bulletin(QDir rulemakerDir, QString timeStamp) override;
};

#endif // RULEMAKERDIALOG_H
