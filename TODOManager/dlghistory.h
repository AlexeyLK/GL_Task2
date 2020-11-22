#ifndef DLGHISTORY_H
#define DLGHISTORY_H

#include <QDialog>
#include "Task.h"

namespace Ui {
class DlgHistory;
}

class DlgHistory : public QDialog
{
    Q_OBJECT

public:
    explicit DlgHistory(Storage *storage, QWidget *parent = nullptr);
    ~DlgHistory();

private slots:
    void on_pbBack_clicked();

    void on_pbClear_clicked();

private:
    Ui::DlgHistory *ui;
    Storage *storage;

    void updateList();
    void clearList();
};

#endif // DLGHISTORY_H
