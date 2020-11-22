#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlghistory.h"

#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // init all the Qt stuff
    ui->setupUi(this);

    // disable button for start/stop task
    ui->pbStartStop->setEnabled(false);

    // set table properties
    QStringList labels;
    labels.append("Task names");
    labels.append("Time to complete");
    labels.append("Description");
    ui->twTaskTable->setColumnCount(3);
    ui->twTaskTable->setHorizontalHeaderLabels(labels);
    ui->twTaskTable->setColumnWidth(0, 200);
    ui->twTaskTable->setColumnWidth(1, 120);
    ui->twTaskTable->setColumnWidth(2, 220);
    ui->twTaskTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // set current time
    ui->lbTime->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));

    // init needed variables
    storageList = new Storage();

    storageList->getFromFile();

    updateList();
    // setup timer to update the time and the remaining time of tasks
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    storageList->SaveMain();
    storageList->Save();
}

// private slots
void MainWindow::timeout()
{
    // update time
    ui->lbTime->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));

    if (storageList->updateTaskList())
    {
        updateList();
    }
}

void MainWindow::addNewTask(Task task)
{
    // do whatever you need with this new task
    storageList->addTask(task);

    updateList();
}

void MainWindow::changeTask(Task task)
{
    storageList->getTasks()->at(ui->twTaskTable->currentRow()).setName(task.getName());
    storageList->getTasks()->at(ui->twTaskTable->currentRow()).setDescription(task.getDescription());
    storageList->getTasks()->at(ui->twTaskTable->currentRow()).setTimeForTask(task.getTimeForTask());
    updateList();
}

void MainWindow::updateList()
{
    // first clear list
    clearList();

    // populate list from storage
    for(size_t i = 0; i < storageList->getTasks()->size(); i++)
    {
        ui->twTaskTable->insertRow(ui->twTaskTable->rowCount());
        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(storageList->getTasks()->at(i).getName())));
        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 2, new QTableWidgetItem(QString::fromStdString(storageList->getTasks()->at(i).getDescription())));

        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(storageList->getTasks()->at(i).getTimeForTask()/unitFactor)));
    }

    // resize columns (comment out this if not desired)
    ui->twTaskTable->resizeRowsToContents();
    ui->twTaskTable->resizeColumnsToContents();

    showStorage();
}

// UI functions
void MainWindow::on_pbEdit_clicked()
{
    // edit selected task
    if (ui->twTaskTable->currentRow() != -1)
    {
        dlgAdd = new DlgAddTask();
        connect(this, SIGNAL(task_edit(Task*)), dlgAdd, SLOT(on_opened_for_change(Task*)));
        connect(dlgAdd, SIGNAL(task_edit(Task)), this, SLOT(changeTask(Task)));

        // get item which should be edited
        emit task_edit(&storageList->getTasks()->at(ui->twTaskTable->currentRow()));

        dlgAdd->exec();

        delete dlgAdd;
    }
    else
    {
        ui->statusbar->showMessage(QString("Please select a task from list. Current selection: %1").arg(ui->twTaskTable->currentRow()), 5000);
    }
}

void MainWindow::on_pbHistory_clicked()
{
    // go to history
    DlgHistory *dlg = new DlgHistory(storageList);
    dlg->exec();

    delete dlg;
}

void MainWindow::on_pbAdd_clicked()
{
    // add new task
    dlgAdd = new DlgAddTask();
    connect(dlgAdd, SIGNAL(task_add(Task)), this, SLOT(addNewTask(Task)));
    dlgAdd->exec();

    ui->pbStartStop->setEnabled(false);
    delete dlgAdd;
}

void MainWindow::on_pbRemove_clicked()
{
    // remove selected task to history
    int idx = ui->twTaskTable->currentRow();
    if (ui->twTaskTable->currentRow() != -1)
    {
        storageList->delTask(storageList->getTasks()->at(idx).getId());
        updateList();
    }
}

void MainWindow::on_pbStartStop_clicked()
{
    if (ui->twTaskTable->currentRow() < (int)storageList->getTasks()->size())
    {
        if (storageList->getTasks()->at(ui->twTaskTable->currentRow()).getStatus() != 1)
        {
            storageList->getTasks()->at(ui->twTaskTable->currentRow()).startWork();
            qDebug() << "started work of " << storageList->getTasks()->at(ui->twTaskTable->currentRow()).getId();
        }
        else
        {
            storageList->getTasks()->at(ui->twTaskTable->currentRow()).finishWork();
            qDebug() << "finished work of " << storageList->getTasks()->at(ui->twTaskTable->currentRow()).getId();
        }

        // update selection
        on_twTaskTable_itemSelectionChanged();
    }
}

void MainWindow::on_twTaskTable_itemSelectionChanged()
{
    // selected item in table changed, get ID of selected element and show it in statusbar
    if (ui->twTaskTable->currentRow() != -1)
    {
        ui->statusbar->clearMessage();
        if (ui->twTaskTable->currentRow() < (int)storageList->getTasks()->size())
        {
            ui->pbStartStop->setEnabled(true);
            qDebug() << "status: " << storageList->getTasks()->at(ui->twTaskTable->currentRow()).getStatus();
            if (storageList->getTasks()->at(ui->twTaskTable->currentRow()).getStatus() != 1)
            {
                ui->pbStartStop->setText("Start");
                ui->pbStartStop->setStyleSheet("QPushButton {\nborder:1px solid #000;\nbackground-color: rgb(0, 170, 0);\nborder-radius:3;\nheight:20px;\nfont-weight:bold;\nwidth:80px;\n}\nQPushButton:pressed {\nbackground-color: rgb(0, 130, 0);\n}");
            }
            else
            {
                ui->pbStartStop->setText("Finish");
                ui->pbStartStop->setStyleSheet("QPushButton {\nborder:1px solid #000;\nbackground-color: rgb(170, 0, 0);\nborder-radius:3;\nheight:20px;\nfont-weight:bold;\nwidth:80px;\n}\nQPushButton:pressed {\nbackground-color: rgb(140, 0, 0);\n}");
            }
            ui->statusbar->showMessage(QString("ID: %1").arg(storageList->getTasks()->at(ui->twTaskTable->currentRow()).getId()), 3000);
        }
        else
            ui->pbStartStop->setEnabled(false);
    }
    else
        ui->pbStartStop->setEnabled(false);
}

void MainWindow::clearList()
{
    // clear table for
    ui->twTaskTable->clearContents();
    ui->twTaskTable->setRowCount(0);
}

// for debug/development
void MainWindow::showStorage()
{
    for (size_t i = 0; i < storageList->getTasks()->size(); i++)
        qDebug() << i
                 << QString::number(storageList->getTasks()->at(i).getId()) << ":"
                 << QString::fromStdString(storageList->getTasks()->at(i).getName()) << ";"
                 << QString::fromStdString(storageList->getTasks()->at(i).getDescription());
}

void MainWindow::showTask(long id)
{
    for (size_t i = 0; i < storageList->getTasks()->size(); i++)
        if (storageList->getTasks()->at(i).getId() == id)
            qDebug() << i
                     << QString::number(storageList->getTasks()->at(i).getId()) << ":"
                     << QString::fromStdString(storageList->getTasks()->at(i).getName()) << ";"
                     << QString::fromStdString(storageList->getTasks()->at(i).getDescription());
}
