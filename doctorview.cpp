#include "doctorview.h"
#include "ui_doctorview.h"
#include "idatabase.h"

DoctorView::DoctorView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单选？
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能直接修改
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initDoctorModel()){
        ui->tableView->setModel(iDatabase.doctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.doctorSelection);
    }
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btnSearch_clicked()
{
    QString filter =QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchDoctor(filter);
}


void DoctorView::on_btnAdd_clicked()
{
    int curRow=IDatabase::getInstance().addNewDoctor();
    emit goDoctorEditView(curRow);
}


void DoctorView::on_btnDel_clicked()
{
    IDatabase::getInstance().deleteCurrentDoctor();
}


void DoctorView::on_btnEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().doctorSelection->currentIndex();
    emit goDoctorEditView(curIndex.row());
}

