#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"

PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单选？
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能直接修改
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.patientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btnAdd_clicked()
{
    int curRow=IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(curRow);
}


void PatientView::on_btnSearch_clicked()//查找患者
{
    QString filter =QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchPatient(filter);
}


void PatientView::on_btnDel_clicked()//删除患者
{
    IDatabase::getInstance().deleteCurrentPatient();
}


void PatientView::on_btnEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().patientSelection->currentIndex();
    emit goPatientEditView(curIndex.row());
}

