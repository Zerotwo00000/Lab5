#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QMainWindow>
#include "loginview.h"
#include "welcomeview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patientview.h"
#include "patienteditview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QMainWindow
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientView();
    void goPatientEditView();
    void goPreviousView();


private slots:
    void on_btn_Back_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btn_Logout_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);
    void updateNavigationButtons();

    Ui::MasterView *ui;

    LoginView *loginView;
    WelcomeView *welcomeView;
    DoctorView *doctorView;
    DepartmentView *departmentView;
    PatientView *patientView;
    PatientEditView *patientEditView;
};
#endif // MASTERVIEW_H
