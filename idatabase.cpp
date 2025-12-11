#include "idatabase.h"
#include <QUuid>

void IDatabase::initDatabase()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="E:\\qtC++\\samples\\LAB_SQLlite\\LAB4.db";
    database.setDatabaseName(aFile);

    //不管你的路径是否正确，都会返回打开
    if(!database.open()){
        qDebug()<<"failed to open database";
    }else {
        qDebug()<<"open database is ok";
    }
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,database);//创建一个SQL表格模型，用于在Qt中操作数据库表
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//手动提交
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);//升序排序
    if(!(patientTabModel->select())) return false;

    patientSelection=new QItemSelectionModel(patientTabModel);//管理视图中的选择状态
    return true;
}

bool IDatabase::initDepartmentModel()
{
    departmentTabModel = new QSqlTableModel(this,database);//创建一个SQL表格模型，用于在Qt中操作数据库表
    departmentTabModel->setTable("department");
    departmentTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//手动提交
    departmentTabModel->setSort(departmentTabModel->fieldIndex("name"),Qt::AscendingOrder);//升序排序
    if(!(departmentTabModel->select())) return false;

    departmentSelection=new QItemSelectionModel(departmentTabModel);//管理视图中的选择状态
    return true;
}

bool IDatabase::initDoctorModel()
{
    doctorTabModel = new QSqlRelationalTableModel(this,database);//创建一个SQL表格模型，用于在Qt中操作数据库表
    doctorTabModel->setTable("doctor");
    doctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//手动提交
    doctorTabModel->setSort(doctorTabModel->fieldIndex("NAME"),Qt::AscendingOrder);//升序排序
    //doctorTabModel->setRelation(doctorTabModel->fieldIndex("DEPARTMENT_ID"),QSqlRelation("department","ID","NAME"));//设置外键关系
    if(!(doctorTabModel->select())) return false;

    doctorSelection=new QItemSelectionModel(doctorTabModel);//管理视图中的选择状态
    return true;
}

int IDatabase::addNewPatient()//添加新患者
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex=patientTabModel->index(patientTabModel->rowCount()-1,1);//创建最后一行的ModelIndex

    int curRecNo=curIndex.row();
    // QSqlRecord curRec=patientTabModel->record(curRecNo);//获取当前记录
    // curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    // curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    // patientTabModel->setRecord(curRecNo,curRec);//写回去
    // 对于 ID (UUID)：
    QModelIndex idIndex = patientTabModel->index(curRecNo, patientTabModel->fieldIndex("ID"));
    patientTabModel->setData(idIndex, QUuid::createUuid().toString(QUuid::WithoutBraces));
    // 对于日期
    QModelIndex createdIndex = patientTabModel->index(curRecNo, patientTabModel->fieldIndex("CREATEDTIMESTAMP"));
    patientTabModel->setData(createdIndex, QDateTime::currentDateTime().toString("yyyy-MM-dd"));

    return curIndex.row();
}

bool IDatabase::searchPatient(QString fliter)
{
    patientTabModel->setFilter(fliter);
    return patientTabModel->select();
}

void IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex=patientSelection->currentIndex();//获取当前选择单元行的模型索引
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();//提交所有挂起的修改到数据库
    patientTabModel->select();//重新从数据库加载数据
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();//提交所有修改
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();//撤销所有修改
}

int IDatabase::addNewDepartment()
{
    departmentTabModel->insertRow(departmentTabModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex=departmentTabModel->index(departmentTabModel->rowCount()-1,1);//创建最后一行的ModelIndex

    int curRecNo=curIndex.row();

    QModelIndex idIndex = departmentTabModel->index(curRecNo, departmentTabModel->fieldIndex("ID"));
    departmentTabModel->setData(idIndex, QUuid::createUuid().toString(QUuid::WithoutBraces));

    return curIndex.row();
}

bool IDatabase::searchDepartment(QString fliter)
{
    departmentTabModel->setFilter(fliter);
    return departmentTabModel->select();
}

void IDatabase::deleteCurrentDepartment()
{
    QModelIndex curIndex=departmentSelection->currentIndex();//获取当前选择单元行的模型索引
    departmentTabModel->removeRow(curIndex.row());
    departmentTabModel->submitAll();//提交所有挂起的修改到数据库
    departmentTabModel->select();//重新从数据库加载数据
}

bool IDatabase::submitDepartmentEdit()
{
    return departmentTabModel->submitAll();//提交所有修改
}

void IDatabase::revertDepartmentEdit()
{
    departmentTabModel->revertAll();//撤销所有修改
}

int IDatabase::addNewDoctor()
{
    doctorTabModel->insertRow(doctorTabModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex=doctorTabModel->index(doctorTabModel->rowCount()-1,1);//创建最后一行的ModelIndex

    int curRecNo=curIndex.row();

    QModelIndex idIndex = doctorTabModel->index(curRecNo, doctorTabModel->fieldIndex("ID"));
    doctorTabModel->setData(idIndex, QUuid::createUuid().toString(QUuid::WithoutBraces));

    return curIndex.row();
}

bool IDatabase::searchDoctor(QString fliter)
{
    doctorTabModel->setFilter(fliter);
    return doctorTabModel->select();
}

void IDatabase::deleteCurrentDoctor()
{
    QModelIndex curIndex=doctorSelection->currentIndex();//获取当前选择单元行的模型索引
    doctorTabModel->removeRow(curIndex.row());
    doctorTabModel->submitAll();//提交所有挂起的修改到数据库
    doctorTabModel->select();//重新从数据库加载数据
}

bool IDatabase::submitDoctorEdit()
{
    // 1. 提交所有挂起的修改到数据库
    if (doctorTabModel->submitAll()) {
        qDebug() << "提交成功。";

        // 2. 【关键】重新从数据库加载数据，确保模型是最新的
        // 这样 DoctorView 中连接到此模型的 QTableView 也会自动更新
        doctorTabModel->select();

        return true;
    } else {
        qDebug() << "提交失败！错误信息：" << doctorTabModel->lastError().text();
        return false;
    }
}

void IDatabase::revertDoctorEdit()
{
    doctorTabModel->revertAll();//撤销所有修改
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");//预处理语句，:USER是占位符由后面的变量替换
    query.bindValue(":USER",userName);
    query.exec();
    if(query.first()&&query.value("username").isValid()){
        QString pwd=query.value("password").toString();
        if(pwd==password) {
            qDebug()<<"login OK";
            return "loginOK";
        }
        else {
            qDebug()<<"wrong password";
            return "wrongPassword";
        }
    }
    else {
        qDebug()<<"no such user"<<userName;
        return "wrongUserName";
    }
}

IDatabase::IDatabase(QObject *parent) : QObject{parent}
{
    initDatabase();
}
