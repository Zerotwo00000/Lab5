#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"

DoctorEditView::DoctorEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::DoctorEditView)
{
    ui->setupUi(this);

    setupDepartmentComboBox();
    dataMapper=new QDataWidgetMapper();
    QSqlRelationalTableModel *tabModel=IDatabase::getInstance().doctorTabModel;
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//在输入框修改马上就更新到模型中

    dataMapper->addMapping(ui->dbEditID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditEmployeeID,tabModel->fieldIndex("EMPLOYEENO"));
    dataMapper->addMapping(ui->dbEditName,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->cbDepartment,tabModel->fieldIndex("DEPARTMENT_ID"));

    dataMapper->setCurrentIndex(index);
}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}

void DoctorEditView::setupDepartmentComboBox()
{
    // 设置部门下拉框模型
    QSqlTableModel *deptModel = IDatabase::getInstance().departmentTabModel;
    ui->cbDepartment->clear();

    // 添加空选项（表示未分配部门）
    ui->cbDepartment->addItem(tr("(未分配)"), "");

    // 填充部门数据
    for (int i = 0; i < deptModel->rowCount(); ++i) {
        QString deptId = deptModel->data(deptModel->index(i, 0)).toString();
        QString deptName = deptModel->data(deptModel->index(i, 1)).toString();
        ui->cbDepartment->addItem(deptName, deptId);
    }
}

void DoctorEditView::on_pushButton_clicked()//保存表单信息到数据库
{
    IDatabase::getInstance().submitDoctorEdit();
    emit goPreviousView();
}


void DoctorEditView::on_pushButton_2_clicked()//撤销
{
    IDatabase::getInstance().revertDoctorEdit();
    emit goPreviousView();
}

