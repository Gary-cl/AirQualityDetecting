#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>


class MyDataBase : public QWidget
{
    Q_OBJECT

public:
    explicit MyDataBase(QWidget *parent = 0);
    ~MyDataBase();

public slots:
    void show();
    void submit();
    void insert(double, double, double);


private:
    bool connect(const QString &);
    QTableView *view;
    QSqlTableModel *model;
};

#endif // MYDATABASE_H
