#ifndef DOCTORVIEW_H
#define DOCTORVIEW_H

#include <QWidget>

namespace Ui {
class DoctorView;
}

class DoctorView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorView(QWidget *parent = nullptr);
    ~DoctorView();

private slots:
    void on_btnSearch_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_btnEdit_clicked();

signals:
    void goDoctorEditView(int index);

private:
    Ui::DoctorView *ui;
};

#endif // DOCTORVIEW_H
