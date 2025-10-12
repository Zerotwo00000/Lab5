#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(UnaryOperatorClicked()));
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(UnaryOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(UnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(UnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double ret=0;
    if(operands.size()==2&&opcode.size()){
        double operand1=operands.front().toDouble();//获取第一个操作数
        operands.pop_front();//这栈怎么跟双向队列一样
        double operand2=operands.front().toDouble();//获取第二个操作数
        operands.pop_front();
        QString op=opcode.front();//取得一个操作符
        opcodes.pop_front();
        //进行运算
        if(op=="+"){
            ret=operand1+operand2;
        }
        else if(op=="-"){
            ret=operand1-operand2;
        }
        else if(op=="×"){
            ret=operand1*operand2;
        }
        else if(op=="÷"){
            ret=operand1/operand2;
        }
        operands.push_back(QString::number(ret));
    }
    else {
        ui->statusbar->showMessage(QString("operands is %1,opcode is %2").arg(operands.size()).arg(opcode.size()));
    }
    return QString::number(ret);
}

void MainWindow::btnNumClicked()
{
    QString digit=qobject_cast<QPushButton*>(sender())->text();//准确获取发送信息的对象,因为有很多数字按钮需要区分
    if(digit=="0"&&operand=="0") digit="";
    if(operand=="0"&&digit!="0") operand="";
    operand+=digit;
    ui->display->setText(operand);
}

void MainWindow::binaryOperatorClicked()
{
    opcode=qobject_cast<QPushButton*>(sender())->text();//记录操作符
    //点击操作符之后让操作数入栈
    if(operand!="") {
        operands.push_back(operand);
        operand="";
        opcodes.push_back(opcode);
        QString ret=calculation();
        ui->display->setText(ret);//可能出现连加，连减等
    }
}

void MainWindow::UnaryOperatorClicked()
{
    if(operand!=""){
        double ret=operand.toDouble();
        operand="";
        QString op=qobject_cast<QPushButton*>(sender())->text();
        if(op=="%") ret/=100.0;
        else if(op=="1/x") ret=1/ret;
        else if(op=="x²") ret*=ret;
        else if(op=="√") ret=sqrt(ret);
        ui->display->setText(QString::number(ret));
    }
}

void MainWindow::on_btnPeriod_clicked()
{
    if(!operand.contains(".")) operand=operand+".";
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    operand=operand.left(operand.length()-1);//从左边开始截取这么多
    ui->display->setText(operand);
}


void MainWindow::on_btnClearAll_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::on_btnEqual_clicked()
{
    if(operand!="") {
        operands.push_back(operand);
        operand="";
        QString ret=calculation();
        ui->display->setText(ret);
    }
}



