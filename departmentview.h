#ifndef DEPARTMENTVIEW_H
#define DEPARTMENTVIEW_H

#include <QWidget>

namespace Ui {
class DepartmentView;
}

class DepartmentView : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentView(QWidget *parent = nullptr);
    ~DepartmentView();

private slots:
    void on_btnSearch_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_btnEdit_clicked();

signals:
    void goDepartmentEditView(int index);

private:
    Ui::DepartmentView *ui;
};

#endif // DEPARTMENTVIEW_H
