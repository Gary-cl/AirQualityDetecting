#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <QWidget>
#include <QTimer>
#include "mygraphstream.h"
#include "led.h"

namespace Ui {
class MyGraph;
}

class MyGraph : public QWidget
{
    Q_OBJECT

public slots:
    void replot();
    void getValue(double, double, double);

public:
    explicit MyGraph(QWidget *parent = 0);
    ~MyGraph();

private:
    void refreshLabel(double, double, double);
    static const int nGraph = 3;
    MyGraphStream dataStream[nGraph];
    QVector<double> x;
    LED *led;
    Ui::MyGraph *ui;
};

#endif // MYGRAPH_H
