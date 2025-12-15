#ifndef DEPARTMENTEDITVIEW_H
#define DEPARTMENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class departmentEditView;
}

class departmentEditView : public QWidget
{
    Q_OBJECT

public:
    explicit departmentEditView(QWidget *parent = nullptr,int index=0);
    ~departmentEditView();

private:
    Ui::departmentEditView *ui;
    QDataWidgetMapper *dataMapper;//数据映射

signals:
    void goPreviousView();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // DEPARTMENTEDITVIEW_H
