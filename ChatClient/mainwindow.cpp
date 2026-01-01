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
    // 检查是否是私聊消息（格式: @用户名 消息内容）
    if(text.startsWith("@")){
        int spaceIndex = text.indexOf(" ");
        if(spaceIndex > 1){  // 有用户名和消息内容
            QString receiver = text.mid(1, spaceIndex - 1).trimmed();
            QString message = text.mid(spaceIndex + 1).trimmed();
            if(!receiver.isEmpty() && !message.isEmpty()){
                m_chatClient->sendPrivateMessage(receiver, message);
                // 立即在本地显示
                displayPrivateMessage(receiver, message, "", true);
                ui->sayLineEdit->clear();
                return;
            }
        }
    }
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
    else if(typeVal.toString().compare("private", Qt::CaseInsensitive) == 0){
        // 处理私聊消息
        const QJsonValue textVal = docObj.value("text");
        const QJsonValue senderVal = docObj.value("sender");
        const QJsonValue receiverVal = docObj.value("receiver");
        const QJsonValue timestampVal = docObj.value("timestamp");

        if(textVal.isNull() || !textVal.isString()) return;
        if(senderVal.isNull() || !senderVal.isString()) return;
        if(receiverVal.isNull() || !receiverVal.isString()) return;

        QString text = textVal.toString();
        QString sender = senderVal.toString();
        QString receiver = receiverVal.toString();
        QString timestamp = timestampVal.isString() ? timestampVal.toString() : "";

        // 判断是否是当前用户发送的私聊
        bool isSentByMe = (sender == m_chatClient->userName());

        // 显示私聊消息
        if(isSentByMe){
            // 这是我发送的消息，sender参数应该是接收者
            displayPrivateMessage(receiver, text, timestamp, true);
        } else {
            // 这是我收到的消息，sender参数应该是发送者
            displayPrivateMessage(sender, text, timestamp, false);
        }
    }
    else if(typeVal.toString().compare("private_error", Qt::CaseInsensitive) == 0){//发送的用户不在线就会出现私聊错误
        // 处理私聊错误
        const QJsonValue textVal = docObj.value("text");
        const QJsonValue receiverVal = docObj.value("receiver");

        if(!textVal.isNull() && textVal.isString()){
            QString errorMsg = textVal.toString();
            QString receiver = receiverVal.isString() ? receiverVal.toString() : "";

            QMessageBox::warning(this, "私聊发送失败",QString("给 %1 的消息发送失败: %2").arg(receiver).arg(errorMsg));
        }
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

void MainWindow::userListReceived(const QStringList &list)
{
    ui->userListWidget->clear();
    ui->userListWidget->addItems(list);
    // 为每个用户项添加提示文本
    for(int i = 0; i < ui->userListWidget->count(); ++i){
        QListWidgetItem *item = ui->userListWidget->item(i);
        QString userName = item->text();

        if(userName.endsWith("*")){
            userName = userName.left(userName.length() - 1);
            if(userName == m_chatClient->userName()){
                item->setToolTip("这是你自己");
            } else {
                item->setToolTip("双击开始私聊");
            }
        } else {
            item->setToolTip("双击开始私聊");
        }
    }
}

//展示私聊信息
void MainWindow::displayPrivateMessage(const QString &sender, const QString &text, const QString &timestamp, bool isSentByMe)
{
    QString timeStr = timestamp.isEmpty() ? QDateTime::currentDateTime().toString("hh:mm:ss") : timestamp;
    QString formattedMsg;
    if(isSentByMe){
        // 我发送的私聊消息
        // 注意：这里的 sender 参数实际上是接收者的名字
        formattedMsg = QString("[%1] 你对 %2 说(私聊): %3").arg(timeStr).arg(sender).arg(text);
    } else {
        // 接收到的私聊消息
        formattedMsg = QString("[%1] %2 对你说(私聊): %3").arg(timeStr).arg(sender).arg(text);
    }
    ui->roomTextEdit->append(formattedMsg);
}


void MainWindow::on_userListWidget_itemDoubleClicked(QListWidgetItem *item)//双击listwidget中的项时会执行的逻辑
{
    //选中某个用户，后面发信息相当于私发，别人收不到私发的消息
    QString userName = item->text();

    // 如果用户名以*结尾（表示自己），则不处理
    if(userName.endsWith("*")){
        return;
    }
    // 在输入框添加私聊前缀
    ui->sayLineEdit->setText("@" + userName + " ");
    ui->sayLineEdit->setFocus();
}

