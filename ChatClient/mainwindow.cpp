#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonValue>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    m_chatClient = new ChatClient(this);//初始化一个客户端

    connect(m_chatClient,&ChatClient::connected,this,&MainWindow::connectedToServer);
    //connect(m_chatClient,&ChatClient::messageReceived,this,&MainWindow::messageReceived);
    connect(m_chatClient,&ChatClient::jsonReceived,this,&MainWindow::jsonReceived);
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
    m_chatClient->disconnectFromHost();//退出登录应该断开连接
    ui->stackedWidget->setCurrentWidget(ui->loginPage);//切换到登录界面
}

void MainWindow::connectedToServer()//服务器连接上之后
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);//切换到聊天室
    m_chatClient->sendMessage(ui->UserNameEdit->text(),"login");
}

void MainWindow::messageReceived(const QString &sender,const QString &text)
{
    ui->roomTextEdit->append(QString("%1 : %2").arg(sender).arg(text));
}

void MainWindow::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal= docObj.value("type");
    if(typeVal.isNull()||!typeVal.isString()) return ;
    if(typeVal.toString().compare("message",Qt::CaseInsensitive)==0){
        const QJsonValue textVal =docObj.value("text");
        const QJsonValue senderVal =docObj.value("sender");
        if(textVal.isNull()||!textVal.isString()) return ;
        if(senderVal.isNull()||!senderVal.isString()) return ;

        messageReceived(senderVal.toString(),textVal.toString());
    }
    else if(typeVal.toString().compare("newuser",Qt::CaseInsensitive)==0){
        const QJsonValue userNameVal =docObj.value("username");
        if(userNameVal.isNull()||!userNameVal.isString()) return ;
        userJoined(userNameVal.toString());//新用户就把他加到用户列表中
    }
}

void MainWindow::userJoined(const QString &user)
{
    ui->userListWidget->addItem(user);
}

