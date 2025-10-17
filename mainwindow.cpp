#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置数字按钮独特的样式
    ui->btnPlus->setProperty("class","op");
    ui->btnMinus->setProperty("class","op");
    ui->btnMultiple->setProperty("class","op");
    ui->btnDivide->setProperty("class","op");
    ui->btnDel->setProperty("class","op");
    ui->btnPeriod->setProperty("class","op");
    ui->btnEqual->setProperty("class","equal");
    QString newStyle=R"(
        QPushButton[class="op"]{
        background-color:#f9f9f9
        }
        QPushButton:hover[class="op"]{
        background-color: #e8e8e8;
        }
        QPushButton[class="equal"]{
        background-color:#1E88E5
        }
    )";
    this->setStyleSheet(this->styleSheet()+newStyle);

    btnNums={
        {Qt::Key_0,ui->btnNum0},
        {Qt::Key_1,ui->btnNum1},
        {Qt::Key_2,ui->btnNum2},
        {Qt::Key_3,ui->btnNum3},
        {Qt::Key_4,ui->btnNum4},
        {Qt::Key_5,ui->btnNum5},
        {Qt::Key_6,ui->btnNum6},
        {Qt::Key_7,ui->btnNum7},
        {Qt::Key_8,ui->btnNum8},
        {Qt::Key_9,ui->btnNum9},
        };
    foreach (auto btn,btnNums) {
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    }
    btnBinarys={
        {Qt::Key_Plus,ui->btnPlus},
        {Qt::Key_Minus,ui->btnMinus},
        {Qt::Key_Asterisk,ui->btnMultiple},
        {Qt::Key_Slash,ui->btnDivide},
    };
    foreach (auto btn, btnBinarys) {
        connect(btn,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    }
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
        ret=operands.front().toDouble();
        //ui->statusbar->showMessage(QString("operands is %1,opcode is %2").arg(operands.size()).arg(opcode.size()));
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
    operands.clear();
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //遍历key值即可
    foreach (auto btnKey, btnNums.keys()) {
        if(btnKey==event->key()) btnNums[btnKey]->animateClick();
    }
    //绑定加减乘除
    foreach (auto btnKey, btnBinarys.keys()) {
        if(btnKey==event->key()) btnBinarys[btnKey]->animateClick();
    }
}




void MainWindow::on_btnSign_clicked()
{
    QString ret=ui->display->text();
    if(ret!="0"&&ret!="0."){ //这两种情况不需要转换符号
        if(ret.indexOf('-')<0){ //看看是否存在减号
            //不存在就添加
            ret="-"+ret;
        }
        else {
            //存在就截取掉-号
            ret=ret.mid(1);
        }
    }
    operand=ret;
    ui->display->setText(operand);
}

