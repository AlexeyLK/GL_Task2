#ifndef DLGADDTASK_H
#define DLGADDTASK_H

#include <QDialog>
#include "Task.h"

namespace Ui {
class DlgAddTask;
}

class DlgAddTask : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAddTask(QWidget *parent = nullptr);
    ~DlgAddTask();

signals:
    void task_add(Task newTask);
    void task_edit(Task task);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

public slots:
    void on_opened_for_change(Task *t);

private:
    Ui::DlgAddTask *ui;
    Task *task;
    bool newItem;
};

#endif // DLGADDTASK_H
