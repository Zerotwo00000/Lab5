#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>//选择文件
#include <QMessageBox>//消息窗口
#include <QTextStream>//读文件
#include <QColorDialog>
#include <QFontDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textChanged=false;

    statusLabel.setMinimumWidth(200);
    statusLabel.setText("length:"+QString::number(0)+"    line:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMinimumWidth(200);
    statusCursorLabel.setText("Ln:"+QString::number(0)+"    Col:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author=new QLabel(ui->statusbar);//调用后可以自动销毁，一定要传个父组件
    author->setText(tr("李宝辉"));
    ui->statusbar->addPermanentWidget(author);

    ui->action_Copy->setEnabled(false);
    ui->action_Paste->setEnabled(false);
    ui->action_Cut->setEnabled(false);
    ui->action_Undo->setEnabled(false);
    ui->action_Redo->setEnabled(false);

    //初始化了反而不好使，因为本来默认就是换行
    QPlainTextEdit::LineWrapMode mode=ui->TextEdit->lineWrapMode();
    if(mode==QTextEdit::NoWrap){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->action_AutoWrap->setChecked(false);
    }
    else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->action_AutoWrap->setChecked(true);
    }

    ui->action_ToolBar->setChecked(true);
    ui->action_StatusBar->setChecked(true);
    ui->action_ShowLineNo->setChecked(true);
    ui->action_AutoSave->setChecked(false);

    autoSaveTimer=new QTimer(this);
    connect(autoSaveTimer, &QTimer::timeout, this, [this]() {
        on_action_Save_triggered();  // 正确调用保存函数
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog dlg;//相当于是创建了一个类
    dlg.exec();
}


void MainWindow::on_action_Find_triggered()
{
    SearchDialog dlg(this,ui->TextEdit);//不能为缺省值
    dlg.exec();
}


void MainWindow::on_action_Replace_triggered()
{
    ReplaceDialog dlg(this,ui->TextEdit);
    dlg.exec();
}


void MainWindow::on_action_New_triggered()
{
    if(!userEditConfirmed()){
        return;
    }

    filePath="";
    ui->TextEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));
    this->setWindowIcon(QIcon(":/new/images/img/newText.png"));//根据路径设置一下窗口图标

    textChanged=false;
}


void MainWindow::on_action_Open_triggered()
{
    if(!userEditConfirmed()){
        return;
    }

    QString filename=QFileDialog::getOpenFileName(this,"打开文件",".",                    //.表示当前目录
                                                    tr("Text files(*.txt);; All(*.*)"));//文件过滤器
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"..","打开文件失败");
        return;
    }

    filePath=filename;//保存路径，后面保存就知道是已经保存过的文件

    QTextStream in(&file);
    QString text=in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();
    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());

    textChanged=false;
}


void MainWindow::on_action_Save_triggered()
{
    QString filename = filePath;

    // 如果是新文件（没有保存过），需要获取保存路径
    if(filename.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this, "保存文件", ".",
                                                tr("Text files(*.txt)"));
        if(filename.isEmpty()) {
            return;  // 用户取消了保存
        }
        filePath = filename;//更换全局路径
    }

    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "错误", "保存文件失败");
        return;
    }

    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();//提取纯文本
    out << text;
    file.close();//close已经包含了file.flush()

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());

    textChanged=false;//保存之后也能让*号在修改后生效
}


void MainWindow::on_action_SaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".",
                                            tr("Text files(*.txt)"));
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "错误", "保存文件失败");
        return;
    }
    filePath = filename;
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    file.close();
    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}


void MainWindow::on_TextEdit_textChanged()
{
    if(!textChanged){
        this->setWindowTitle("*"+this->windowTitle());
        textChanged=true;
    }

    statusLabel.setText("length:"+QString::number(ui->TextEdit->toPlainText().length())
                        +"    line:"+QString::number(ui->TextEdit->document()->lineCount()));
}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){
        QString path=(filePath!="")?filePath:"无标题.txt";

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n")+"\""+path+"\"?");
        msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        int r=msg.exec();
        switch(r){
        case QMessageBox::Yes:
            on_action_Save_triggered();
            break;
        case QMessageBox::No:
            textChanged=false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }
    return true;
}


void MainWindow::on_action_Undo_triggered()
{
    ui->TextEdit->undo();
}


void MainWindow::on_action_Redo_triggered()
{
    ui->TextEdit->redo();
}


void MainWindow::on_action_Cut_triggered()
{
    ui->TextEdit->cut();
    ui->action_Paste->setEnabled(true);
}


void MainWindow::on_action_Copy_triggered()
{
    ui->TextEdit->copy();
    ui->action_Paste->setEnabled(true);
}


void MainWindow::on_action_Paste_triggered()
{
    ui->TextEdit->paste();
}


void MainWindow::on_TextEdit_copyAvailable(bool b)
{
    ui->action_Copy->setEnabled(b);
    ui->action_Cut->setEnabled(b);
}


void MainWindow::on_TextEdit_redoAvailable(bool b)
{
    ui->action_Redo->setEnabled(b);
}


void MainWindow::on_TextEdit_undoAvailable(bool b)
{
    ui->action_Undo->setEnabled(b);
}


void MainWindow::on_action_SelectAll_triggered()
{
    ui->TextEdit->selectAll();
}


void MainWindow::on_action_FontColor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit{color:%1}").arg(color.name()));
    }
}


void MainWindow::on_action_FontBackgroundColor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit{background-color:%1}").arg(color.name()));
    }
}


void MainWindow::on_action_AutoWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode=ui->TextEdit->lineWrapMode();
    if(mode==QTextEdit::NoWrap){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->action_AutoWrap->setChecked(true);
    }
    else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->action_AutoWrap->setChecked(false);
    }
}


void MainWindow::on_action_Font_triggered()
{
    bool ok=false;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok) ui->TextEdit->setFont(font);
}


void MainWindow::on_action_EditorBackgroundColor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        this->setStyleSheet(QString("QMainWindow{background-color:%1}").arg(color.name()));
    }
    //设计编辑器背景颜色，没法了只能拿mainwindow来了哈哈
}


void MainWindow::on_action_ToolBar_triggered()
{
    bool visible=ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->action_ToolBar->setChecked(!visible);
}


void MainWindow::on_action_StatusBar_triggered()
{
    bool visible=ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->action_StatusBar->setChecked(!visible);
}


void MainWindow::on_action_Exit_triggered()
{
    if(userEditConfirmed()){
        exit(0);
    }
}


void MainWindow::on_TextEdit_cursorPositionChanged()
{
    int col=0;
    int ln=0;
    int flg=-1;
    int pos=ui->TextEdit->textCursor().position();//获取的是在整个文本中的位置
    QString text=ui->TextEdit->toPlainText();//获取到纯文本
    for(int i=0;i<pos;i++){
        if(text[i]=='\n'){
            ln++;
            flg=i;
        }
    }
    flg++;
    col=pos-flg;
    statusCursorLabel.setText("Ln:"+QString::number(ln+1)+"    Col:"+QString::number(col+1));
}


void MainWindow::on_action_ShowLineNo_triggered()
{
    // 获取当前行号显示状态
    bool IsVisible = ui->TextEdit->isLineNumbersVisible();
    ui->TextEdit->setLineNumbersVisible(!IsVisible);
    ui->action_ShowLineNo->setChecked(!IsVisible);
}


void MainWindow::on_action_AutoSave_triggered()
{
    if(ui->action_AutoSave->isChecked()){
        autoSaveTimer->start(3000);  // 3秒
    }
    else {
        autoSaveTimer->stop();
    }
}

