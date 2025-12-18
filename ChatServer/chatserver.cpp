#include "chatserver.h"
#include <QDebug>
#include <QJsonValue>
#include <QJsonObject>

ChatServer::ChatServer(QObject *parent):
    QTcpServer(parent)
{

}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker= new ServerWorker(this);
    if(!worker->setSocketDescriptor(socketDescriptor)){
        worker->deleteLater();
        return;
    }
    connect(worker,&ServerWorker::logMessage,this,&ChatServer::logMessage);
    connect(worker,&ServerWorker::jsonReceived,this,&ChatServer::jsonReceived);
    m_clients.append(worker);//成功了就添加进来
    emit logMessage("新的用户连接上了");
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for(ServerWorker *worker : m_clients){
        worker->sendJson(message);
    }
}

void ChatServer::stopServer()
{
    close();
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &docObj)//处理接收到的json信息
{
    const QJsonValue typeVal= docObj.value("type");
    if(typeVal.isNull()||!typeVal.isString()) return ;
    if(typeVal.toString().compare("message",Qt::CaseInsensitive)==0){
        const QJsonValue textVal =docObj.value("text");
        if(textVal.isNull()||!textVal.isString()) return ;
        const QString text= textVal.toString().trimmed();
        if(text.isEmpty()) return ;
        QJsonObject message;
        message["type"] = "message";
        message["text"] = text;
        message["sender"] = sender->userName();
        broadcast(message,sender);
    }
    else if(typeVal.toString().compare("login",Qt::CaseInsensitive)==0){
        const QJsonValue userNameVal =docObj.value("text");
        if(userNameVal.isNull()||!userNameVal.isString()) return ;
        sender->setUserName(userNameVal.toString());//把登录的用户名传过来设置好，后面发消息才能获取到用户名
        QJsonObject connectedMessage;
        connectedMessage["type"] = "newuser";
        connectedMessage["username"] = userNameVal.toString();
        broadcast(connectedMessage,sender);
    }
}
