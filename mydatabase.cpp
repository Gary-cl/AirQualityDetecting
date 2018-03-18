#include "mydatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTimer>
#include <QSqlError>
#include <QHeaderView>

MyDataBase::MyDataBase(QWidget *parent) :
    QWidget(parent)
{
    QTimer *tm = new QTimer(this);
    QObject::connect(tm, &QTimer::timeout, this, &MyDataBase::submit);
    tm->start(1000);

    if (connect("data.db")) {
        model = new QSqlTableModel;
        model->setTable("pm");
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("id"));
        model->setHeaderData(1, Qt::Horizontal, tr("pm2_5"));
        model->setHeaderData(2, Qt::Horizontal, tr("pm5"));
        model->setHeaderData(3, Qt::Horizontal, tr("pm10"));


        view = new QTableView;
        view->setModel(model);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->resizeColumnsToContents();
        view->setColumnHidden(0, true);
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QHeaderView *header = view->horizontalHeader();
        header->setStretchLastSection(true);    //最右列填充
    }
    else
    {
        QMessageBox::warning(this, "error", model->lastError().text());

    }
}

MyDataBase::~MyDataBase()
{
    delete model;
    model = NULL;
    delete view;
    view = NULL;
}

void MyDataBase::submit()
{
    model->submitAll();
    model->select();
}

void MyDataBase::show()
{
    view->show();
}

void MyDataBase::insert(double pm2_5, double pm5, double pm10)
{
    int rowCount = model->rowCount();
    model->insertRow(rowCount);
    model->setData(model->index(rowCount,1),pm2_5);
    model->setData(model->index(rowCount,2),pm5);
    model->setData(model->index(rowCount,3),pm10);
}


bool MyDataBase::connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if(!db.open())
        return false;
    QSqlQuery query;
    query.exec("create table pm (id int primary key, pm2_5 vchar, pm5 vchar, pm10 vchar)");
    query.exec("insert into pm values (0, ,1 ,2, 3)");
    query.exec("insert into pm values (0, ,1 ,2, 3)");
    query.exec("insert into pm values (0, ,1 ,2, 3)");
    return true;
}
