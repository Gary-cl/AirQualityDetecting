#include "mygraph.h"
#include "ui_mygraph.h"

const int MAX_BUF = 255;

MyGraph::MyGraph(QWidget *parent) :
    QWidget(parent),
    dataStream({MAX_BUF, MAX_BUF, MAX_BUF}),
    ui(new Ui::MyGraph)
{
    //qcustomplot初始化
    ui->setupUi(this);
    ui->qcustomplot->addGraph();
    ui->qcustomplot->addGraph();
    ui->qcustomplot->addGraph();
    ui->qcustomplot->xAxis->setLabel("x");
    ui->qcustomplot->yAxis->setLabel("y");
    ui->qcustomplot->resize(400, 300);
    ui->qcustomplot->xAxis->setRange(0, MAX_BUF);
    ui->qcustomplot->yAxis->setRange(0, 500);

    //曲线颜色
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    ui->qcustomplot->graph(0)->setPen(pen);
    pen.setColor(Qt::red);
    ui->qcustomplot->graph(1)->setPen(pen);
    pen.setColor(Qt::yellow);
    ui->qcustomplot->graph(2)->setPen(pen);

    //x轴
    for (int i = 0; i < MAX_BUF; ++i)
    {
        x.push_back(i);
    }

    //LED
    led = new LED(this);
    ui->led->addWidget(led);
    led->update();

    //定时器
    QTimer *tm = new QTimer(this);
    connect(tm, &QTimer::timeout, this, &MyGraph::replot);
    tm->start(1000);
}

void MyGraph::refreshLabel(double pm2_5, double pm5, double pm10)
{
    ui->pm2_5->setNum(pm2_5);
    ui->pm5->setNum(pm5);
    ui->pm10->setNum(pm10);


    //计算AQI 基于pm2.5
    static QColor ledColor= Qt::green;
    static int AQI = 0;
    static int LAQI[8] = {0, 50, 100, 150, 200, 300, 400, 500}; //空气质量指数标准
    static int ug_pm[8] = {0, 35, 75, 115, 150, 250, 350, 500}; //pm2.5浓度标准 um/m^3
    for (int i = 1; i < 8; ++i)
    {
        if (pm2_5 <= ug_pm[i])
        {
            //AQI计算公式
            AQI = (LAQI[i] - LAQI[i-1]) / (double)(ug_pm[i] - ug_pm[i-1]) * (pm2_5 - ug_pm[i-1]) + LAQI[i-1];
            break;
        }
    }

    ui->AQI->setNum(AQI);


    //刷新LED
    QColor newColor;
    if (AQI <= 50)
    {
        newColor = Qt::green;
    }
    else if (AQI <= 100)
    {
        newColor = Qt::yellow;
    }
    else if (AQI <= 150)
    {
        newColor = QColor(255, 100, 0);//orange
    }
    else if (AQI <= 200)
    {
        newColor = Qt::red;
    }
    else if (AQI <= 300)
    {
        newColor = Qt::darkRed;
    }
    else
    {
        newColor = Qt::black;
    }

    if (newColor != ledColor)
    {
        this->led->setColor(newColor);
        ledColor = newColor;
        this->led->update();//立即刷新LED
    }
}

void MyGraph::getValue(double pm2_5, double pm5, double pm10)
{
    this->dataStream[0].enqueue(pm2_5);
    this->dataStream[1].enqueue(pm5);
    this->dataStream[2].enqueue(pm10);

    this->refreshLabel(pm2_5, pm5, pm10);
}

void MyGraph::replot()
{
    QVector<double> y;

    //pm2.5
    if (ui->checkBox2_5->isChecked())
        y = dataStream[0].buf;
    else
        y.clear();
    while (y.size() < MAX_BUF)
    {
        y.push_back(0);
    }
    ui->qcustomplot->graph(0)->setData(x, y);

    //pm5
    if (ui->checkBox5->isChecked())
        y = dataStream[1].buf;
    else
        y.clear();
    while (y.size() < MAX_BUF)
    {
        y.push_back(0);
    }
    ui->qcustomplot->graph(1)->setData(x, y);

    //pm10
    if (ui->checkBox10->isChecked())
        y = dataStream[2].buf;
    else
        y.clear();
    while (y.size() < MAX_BUF)
    {
        y.push_back(0);
    }
    ui->qcustomplot->graph(2)->setData(x, y);


    ui->qcustomplot->replot(); //绘制曲线
}


MyGraph::~MyGraph()
{
    delete ui;
}
