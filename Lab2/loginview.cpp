#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btnSignIn_clicked()
{
    //获取到输入框的用户名和密码
    QString status=IDatabase::getInstance().userLogin(ui->inputUserName->text(),ui->inputPassword->text());
    if(status=="loginOK") emit loginSuccess();//登录状态是ok则进入到欢迎界面
}

