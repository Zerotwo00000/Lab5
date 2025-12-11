#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class DoctorEditView;
}

class DoctorEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditView(QWidget *parent = nullptr,int index=0);
    ~DoctorEditView();

private:
    Ui::DoctorEditView *ui;
    QDataWidgetMapper *dataMapper;//数据映射
    void setupDepartmentComboBox();

signals:
    void goPreviousView();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // DOCTOREDITVIEW_H
