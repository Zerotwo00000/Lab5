#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QMessageBox>

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
    // 连接用户列表双击信号
    connect(ui->userListWidget, &QListWidget::itemDoubleClicked,this, &MainWindow::on_userListWidget_itemDoubleClicked);
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
    QString text = ui->sayLineEdit->text().trimmed();
    if(text.isEmpty()) return;
    // 普通群聊消息
    m_chatClient->sendMessage(text);
    ui->sayLineEdit->clear();//发完清空才是正确的
}


void MainWindow::on_logoutBtn_clicked()
{
    m_chatClient->disconnectFromHost();//退出登录应该断开连接
    ui->stackedWidget->setCurrentWidget(ui->loginPage);//切换到登录界面

    for(auto aItem: ui->userListWidget->findItems(ui->UserNameEdit->text(),Qt::MatchExactly)){//退出登录后把用户删除
        ui->userListWidget->removeItemWidget(aItem);
        delete aItem;
    }
}

void MainWindow::connectedToServer()//服务器连接上之后
{
    m_chatClient->sendMessage(ui->UserNameEdit->text(),"login");
    ui->stackedWidget->setCurrentWidget(ui->chatPage);//切换到聊天室
}

void MainWindow::messageReceived(const QString &sender,const QString &text)
{
    ui->roomTextEdit->append(QString("%1 : %2").arg(sender).arg(text));
}

void MainWindow::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal= docObj.value("type");
    if(typeVal.isNull()||!typeVal.isString()) return ;
    if(typeVal.toString().compare("login_success", Qt::CaseInsensitive) == 0){
        // 登录成功，设置用户名
        const QJsonValue userNameVal = docObj.value("username");
        if(!userNameVal.isNull() && userNameVal.isString()){
            m_chatClient->setUserName(userNameVal.toString());
        }
    }
    else if(typeVal.toString().compare("message",Qt::CaseInsensitive)==0){
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
        //m_chatClient->setUserName(userNameVal.toString());//设置客户端用户名
    }
    //处理其它客户端收到其它用户下线的逻辑
    else if(typeVal.toString().compare("userdisconnected",Qt::CaseInsensitive)==0){
        const QJsonValue userNameVal =docObj.value("username");
        if(userNameVal.isNull()||!userNameVal.isString()) return ;
        userLeft(userNameVal.toString());//在用户列表中移除掉下线的用户
    }
    //处理新登录进来的用户没有以前用户列表信息的逻辑
    else if(typeVal.toString().compare("userlist",Qt::CaseInsensitive)==0){
        const QJsonValue userlistVal =docObj.value("userlist");
        if(userlistVal.isNull()||!userlistVal.isArray()) return ;
        userListReceived(userlistVal.toVariant().toStringList());
    }
    else if(typeVal.toString().compare("loginfailed", Qt::CaseInsensitive) == 0){//这个效果还是很好实现的
        // 处理登录失败
        const QJsonValue reasonVal = docObj.value("reason");
        QString reason = "登录失败";
        if(!reasonVal.isNull() && reasonVal.isString()){
            reason = reasonVal.toString();
        }
        QMessageBox::warning(this, "登录失败", reason);
        // 断开连接
        m_chatClient->disconnectFromHost();
        // 切换回登录页面
        ui->stackedWidget->setCurrentWidget(ui->loginPage);
    }
}

void MainWindow::userJoined(const QString &user)
{
    ui->userListWidget->addItem(user);
}

void MainWindow::userLeft(const QString &user)
{
    for(auto aItem: ui->userListWidget->findItems(user,Qt::MatchExactly)){//退出登录后把用户删除
        ui->userListWidget->removeItemWidget(aItem);
        delete aItem;
    }
}





