#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dlgaddtask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
//    void closeEvent(QCloseEvent *event) override;

signals:
    void task_edit(Task *t);

private slots:
    // UI
    void on_pbEdit_clicked();
    void on_pbHistory_clicked();
    void on_pbAdd_clicked();
    void on_pbRemove_clicked();

    // logic
    void timeout();
    void addNewTask(Task task);
    void changeTask(Task task);
    void on_twTaskTable_itemSelectionChanged();
    void on_pbStartStop_clicked();

private:
    Ui::MainWindow *ui;
    DlgAddTask *dlgAdd;

    // storage member
    Storage *storageList;

    void clearList();
    void updateList();

    // for debug/development
    void showStorage();
    void showTask(long id);
};
#endif // MAINWINDOW_H
