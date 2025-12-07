#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget *parent,QPlainTextEdit *TextEdit)//对话框类无法直接访问主窗口的控件
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    pTextEdit=TextEdit;
    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btnNext_clicked()
{
    QString target=ui->searchEdit->text();
    if(target==""||pTextEdit==nullptr) return;

    QString text=pTextEdit->toPlainText();
    QTextCursor c=pTextEdit->textCursor();
    int index=-1;

    if(ui->rbDown->isChecked()){
        index=text.indexOf(target,c.position(),ui->chkCase->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive);
        if(index>=0){
            c.setPosition(index);
            c.setPosition(index+target.length(),QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }
    else if(ui->rbUp->isChecked()){
        index=text.lastIndexOf(target,c.position()-text.length()-1,ui->chkCase->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive);
        if(index>=0){
            c.setPosition(index+target.length());
            c.setPosition(index,QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }

    if(index<0){
        QMessageBox msg(this);
        msg.setWindowTitle("Tips");
        msg.setText(QString("找不到")+target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void ReplaceDialog::on_btnReplace_clicked()
{
    QString target=ui->searchEdit->text();
    QString to=ui->targetEdit->text();

    if((pTextEdit!=nullptr)&&(target!="")&&(to!="")){
        QString selText=pTextEdit->textCursor().selectedText();
        if(selText==target) pTextEdit->insertPlainText(to);
        on_btnNext_clicked();
    }
}


void ReplaceDialog::on_btnReplaceAll_clicked()
{
    QString target=ui->searchEdit->text();
    QString to=ui->targetEdit->text();

    if((pTextEdit!=nullptr)&&(target!="")&&(to!="")){
        QString text=pTextEdit->toPlainText();
        text.replace(target,to,ui->chkCase->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive);
        pTextEdit->clear();
        pTextEdit->insertPlainText(text);
    }
}


void ReplaceDialog::on_btnCancel_clicked()
{
    accept();
}

