#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mySocket = new MySocket(this);
    myGraph = new MyGraph(this);
    myDataBase = new MyDataBase;
    ui->MySocket->addWidget(mySocket);
    ui->MyGraph->addWidget(myGraph);


    connect(mySocket, &MySocket::sendValue, myGraph, &MyGraph::getValue);
    connect(mySocket, &MySocket::disp, myDataBase, &MyDataBase::show);
    connect(mySocket, &MySocket::sendValue, myDataBase, &MyDataBase::insert);
}

MainWindow::~MainWindow()
{
    delete myDataBase;
    myDataBase = NULL;

    delete ui;
}
