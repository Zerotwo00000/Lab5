#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>

MasterView::MasterView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    //this->setWindowFlag(Qt::FramelessWindowHint);隐藏边框

    goLoginView();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);
    connect(loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));
}

void MasterView::goWelcomeView()
{
    welcomeView=new WelcomeView(this);
    pushWidgetToStackView(welcomeView);
}

void MasterView::goDoctorView()
{
    doctorView=new DoctorView(this);
    pushWidgetToStackView(doctorView);
}

void MasterView::goDepartmentView()
{
    departmentView=new DepartmentView(this);
    pushWidgetToStackView(departmentView);
}

void MasterView::goPatientView()
{
    patientView=new PatientView(this);
    pushWidgetToStackView(patientView);
}

void MasterView::goPatientEditView()
{
    patientEditView=new PatientEditView(this);
    pushWidgetToStackView(patientEditView);
}

void MasterView::goPreviousView()
{
    int count =ui->stackedWidget->count();
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->label_Title->setText(ui->stackedWidget->currentWidget()->windowTitle());
        QWidget *widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
        updateNavigationButtons();//强制再刷新一次，因为更换页面的函数比删除触发的更早，导致窗口个数没变
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count=ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);
    ui->label_Title->setText(widget->windowTitle());
}

void MasterView::updateNavigationButtons()
{
    int count = ui->stackedWidget->count();

    // 1. 根据页面数更新返回按钮状态
    if(count > 1) {
        ui->btn_Back->setEnabled(true);
    } else {
        ui->btn_Back->setEnabled(false);
    }

    // 2. 根据当前页面标题更新注销/返回按钮状态
    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if (title == "欢迎") {
        ui->btn_Logout->setEnabled(true);
        // 特殊处理：欢迎页面是主页，不应有返回
        ui->btn_Back->setEnabled(false);
    } else {
        ui->btn_Logout->setEnabled(false);
    }
}


void MasterView::on_btn_Back_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    updateNavigationButtons();
}


void MasterView::on_btn_Logout_clicked()
{
    goPreviousView();
}

