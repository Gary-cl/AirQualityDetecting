#include "mysocket.h"
#include "ui_mysocket.h"


MySocket::MySocket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MySocket)
{
    ui->setupUi(this);

    socketHandler = new MySocketHandler(this);

    QObject::connect(this, &MySocket::connect, socketHandler, &MySocketHandler::cnt);
    QObject::connect(this, &MySocket::disconnect, socketHandler, &MySocketHandler::dcnt);
    QObject::connect(this, &MySocket::sendData, socketHandler, &MySocketHandler::send);


    ui->connect->setEnabled(true);
    //ui->send->setEnabled(false);
}

MySocket::~MySocket()
{
    delete ui;
}


void MySocket::getValue(double pm2_5, double pm5, double pm10)
{
    emit sendValue(pm2_5, pm5, pm10);
}

void MySocket::connected()
{
    ui->connect->setText("断开连接");
    ui->connect->setEnabled(true);
    //ui->send->setEnabled(true);
    emit this->sendData("{\"methon\" : \"select\", \"value\" : [\"pm2.5\", \"pm5\", \"pm10\"]}");
}

void MySocket::disconnected()
{
    ui->connect->setText("连接");
    ui->connect->setEnabled(true);
    //ui->send->setEnabled(false);
}

void MySocket::getError(QString err)
{
    QMessageBox::warning(this, "error", err);
}


void MySocket::getBuffer(QByteArray buffer)
{
    //ui->textBrowser->append(buffer);
}

void MySocket::on_send_clicked()
{
    //emit this->sendData(ui->textEdit->toPlainText().toLatin1());
}


void MySocket::on_connect_clicked()
{
    if (tr("连接") == ui->connect->text())
    {
        QString addr = ui->address->text();
        int po = ui->port->text().toInt();
        emit this->connect(addr, po);

    }
    else if (tr("断开连接") == ui->connect->text())
        emit this->disconnected();

    //ui->connect->setEnabled(false);
}

void MySocket::on_pushButton_clicked()
{
    emit this->disp();
}
