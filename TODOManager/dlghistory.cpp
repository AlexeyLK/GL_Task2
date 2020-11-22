#include "dlghistory.h"
#include "ui_dlghistory.h"

#include <QDebug>
#include <QDateTime>

DlgHistory::DlgHistory(Storage *_storage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgHistory),
    storage(_storage)
{
    ui->setupUi(this);

    // set icon to button
    ui->pbBack->setIcon(QIcon(QPixmap(":/back.png")));
    ui->pbBack->setIconSize(QSize(16,16));

    // set table properties
    QStringList labels;
    labels.append("ID");
    labels.append("Tasks");
    labels.append("start - finish");
    labels.append("total work time - days : hours : minuts : seconds");
    labels.append("status");
    ui->twTaskTable->setColumnCount(5);
    ui->twTaskTable->setHorizontalHeaderLabels(labels);
    ui->twTaskTable->setColumnWidth(0, 50);
    ui->twTaskTable->setColumnWidth(1, 120);
    ui->twTaskTable->setColumnWidth(2, 400);
    ui->twTaskTable->setColumnWidth(3, 100);
    ui->twTaskTable->setColumnWidth(4, 100);
    ui->twTaskTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    storage->getHisFromFile();

    updateList();
}

DlgHistory::~DlgHistory()
{
    delete ui;
}

void DlgHistory::on_pbBack_clicked()
{
    this->close();
}

void DlgHistory::on_pbClear_clicked()
{
    storage->delHistoryTask();
    updateList();
}

void DlgHistory::updateList()
{
    qDebug() << "total " << storage->getHTasks().size() << " history tasks";

    clearList();

    // show storage items
    for(size_t i = 0; i < storage->getHTasks().size(); i++)
    {

        // use here factors to calculate desired unit (hours, days etc.)
        ui->twTaskTable->insertRow(ui->twTaskTable->rowCount());

        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(storage->getHTasks()[i].getId())));

        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(storage->getHTasks()[i].getName())));
   // qDebug()<< storage->getHTasks()[i].getFinTime();
        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 2, new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(storage->getHTasks()[i].getSTime()).toString()+"  -  " + QDateTime::fromSecsSinceEpoch( storage->getHTasks()[i].getFinTime()).toString()) );

         long time = storage->getHTasks()[i].getTotalTime();
         long time_s =  time % 60;
         long time_m = time / 60;
         long time_h = time_m / 60;
         long time_d = time_h / 24;

        //ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(storage->getHTasks()[i].getTotalTime())));
        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(time_d) + " : " +QString::number(time_h) + " : " +QString::number(time_m) + " : " +  QString::number(time_s) ) );

        // icons can be set like that
        QTableWidgetItem *state_item = new QTableWidgetItem;

        switch(storage->getHTasks()[i].getStatus())
        {
        case 0:
            state_item->setIcon(QIcon(":/ok.png"));
            break;
        case 1:
            // ...
            break;
        default:
            state_item->setIcon(QIcon(":/nok.png"));
            break;
        }

        ui->twTaskTable->setItem(ui->twTaskTable->rowCount() - 1, 4, state_item);
    }
}

void DlgHistory::clearList()
{
    ui->twTaskTable->clearContents();
    ui->twTaskTable->setRowCount(0);
}
