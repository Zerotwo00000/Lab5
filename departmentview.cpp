#include "departmentview.h"
#include "ui_departmentview.h"
#include "idatabase.h"

DepartmentView::DepartmentView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DepartmentView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单选？
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能直接修改
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initDepartmentModel()){
        ui->tableView->setModel(iDatabase.departmentTabModel);
        ui->tableView->setSelectionModel(iDatabase.departmentSelection);
    }
}

DepartmentView::~DepartmentView()
{
    delete ui;
}

void DepartmentView::on_btnSearch_clicked()
{
    QString filter =QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchDepartment(filter);
}


void DepartmentView::on_btnAdd_clicked()
{
    int curRow=IDatabase::getInstance().addNewDepartment();
    emit goDepartmentEditView(curRow);
}


void DepartmentView::on_btnDel_clicked()
{
    IDatabase::getInstance().deleteCurrentDepartment();
}


void DepartmentView::on_btnEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().departmentSelection->currentIndex();
    emit goDepartmentEditView(curIndex.row());
}

