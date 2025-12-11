#include "departmenteditview.h"
#include "ui_departmenteditview.h"
#include <QSqlTableModel>
#include "idatabase.h"

departmentEditView::departmentEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::departmentEditView)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().departmentTabModel;
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//在输入框修改马上就更新到模型中

    dataMapper->addMapping(ui->dbEditID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName,tabModel->fieldIndex("NAME"));

    dataMapper->setCurrentIndex(index);
}

departmentEditView::~departmentEditView()
{
    delete ui;
}

void departmentEditView::on_pushButton_clicked()
{
    IDatabase::getInstance().submitDepartmentEdit();
    emit goPreviousView();
}


void departmentEditView::on_pushButton_2_clicked()
{
    IDatabase::getInstance().revertDepartmentEdit();
    emit goPreviousView();
}

