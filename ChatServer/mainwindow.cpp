#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_chatServer=new ChatServer(this);

    connect(m_chatServer,&ChatServer::logMessage,this,&MainWindow::logMessage);
    ui->startStopButton->setText("启动服务器");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startStopButton_clicked()
{
    // static bool started=false;//声明的是静态变量，应该是只定义一次
    // if(started){
    //     ui->startStopButton->setText("停止服务器");
    //     logMessage("服务器已经启动");
    // }
    // else {
    //     ui->startStopButton->setText("启动服务器");
    //     logMessage("服务器已经停止");
    // }
    // started=!started;
    if(m_chatServer->isListening()){ // 如果服务器正在监听（运行中）
        m_chatServer->stopServer();
        ui->startStopButton->setText("启动服务器");
        logMessage("服务器已停止");
    }
    else{
        if(!m_chatServer->listen(QHostAddress::Any,1967)){ //尝试启动服务器，监听所有网络接口
            QMessageBox::critical(this,"错误","无法启动服务器");
            return;
        }
        logMessage("服务器已启动");
        ui->startStopButton->setText("停止服务器");
    }
}

void MainWindow::logMessage(const QString &msg)
{
    ui->logEditer->appendPlainText(msg);
}

