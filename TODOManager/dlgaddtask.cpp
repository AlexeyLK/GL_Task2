#include "dlgaddtask.h"
#include "ui_dlgaddtask.h"

#include <QMessageBox>
#include <QDebug>


DlgAddTask::DlgAddTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAddTask)
{
    ui->setupUi(this);

    this->setWindowTitle("Add item");
    newItem = true;
}

DlgAddTask::~DlgAddTask()
{
    delete ui;
}

void DlgAddTask::on_buttonBox_accepted()
{
    if (ui->leTaskName->text().isEmpty() || ui->leTaskDesc->text().isEmpty() || ui->leTaskDuration->text().isEmpty())
    {
        QMessageBox::warning(this, "Missing entries", "Please fill all fields");
    }
    else
    {
        if (newItem == true)
        {
            // get info from text inputs
            task = new Task(ui->leTaskName->text().toStdString(), ui->leTaskDesc->text().toStdString(), ui->leTaskDuration->text().toInt()*unitFactor);

            emit task_add(*task);
        }
        else
        {
            task->setName(ui->leTaskName->text().toStdString());
            task->setDescription(ui->leTaskDesc->text().toStdString());
            task->setTimeForTask(ui->leTaskDuration->text().toInt()*unitFactor);

            emit task_edit(*task);
        }
        this->close();
    }
}

void DlgAddTask::on_opened_for_change(Task *t)
{
    ui->leTaskName->setText(QString::fromStdString(t->getName()));
    ui->leTaskDesc->setText(QString::fromStdString(t->getDescription()));
    ui->leTaskDuration->setText(QString::number(t->getTimeForTask()/unitFactor));
    task = t;
    newItem = false;
}

void DlgAddTask::on_buttonBox_rejected()
{
    this->close();
}
