#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    m_chatClient = new ChatClient(this);//初始化一个客户端

    connect(m_chatClient,&ChatClient::connected,this,&MainWindow::connectedToServer);
    connect(m_chatClient,&ChatClient::messageReceived,this,&MainWindow::messageReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    m_chatClient->connectToServer(QHostAddress(ui->ServerEdit->text()),1967);
}


void MainWindow::on_sayBtn_clicked()
{
    if(!ui->sayLineEdit->text().isEmpty()) m_chatClient->sendMessage(ui->sayLineEdit->text());
}


void MainWindow::on_logoutBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);//切换到登录界面
}

void MainWindow::connectedToServer()//服务器连接上之后
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);//切换到聊天室
    m_chatClient->sendMessage(ui->UserNameEdit->text(),"login");
}

void MainWindow::messageReceived(const QString &text)
{
    ui->roomTextEdit->append(text);
}

