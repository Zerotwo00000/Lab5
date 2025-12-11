#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

class IDatabase : public QObject
{
    Q_OBJECT
public:

    static IDatabase& getInstance()
    {
        static IDatabase instance;
        return instance;
    }

    QString userLogin(QString userName,QString password);

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const&) = delete;
    void operator=(IDatabase const&)  = delete;

    QSqlDatabase database;

    void initDatabase();

signals:

public:
    bool initPatientModel();
    bool initDepartmentModel();
    bool initDoctorModel();

    int addNewPatient();
    bool searchPatient(QString fliter);
    void deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    int addNewDepartment();
    bool searchDepartment(QString fliter);
    void deleteCurrentDepartment();
    bool submitDepartmentEdit();
    void revertDepartmentEdit();

    int addNewDoctor();
    bool searchDoctor(QString fliter);
    void deleteCurrentDoctor();
    bool submitDoctorEdit();
    void revertDoctorEdit();

    QSqlTableModel *patientTabModel; //数据模型
    QItemSelectionModel *patientSelection;//选择模型

    QSqlTableModel *departmentTabModel; //数据模型
    QItemSelectionModel *departmentSelection;//选择模型

    QSqlRelationalTableModel *doctorTabModel; //数据模型
    QItemSelectionModel *doctorSelection;//选择模型

};

#endif // IDATABASE_H
