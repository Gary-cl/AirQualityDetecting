#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QWidget>
#include <QTcpSocket>
#include "mysockethandler.h"
#include <QMessageBox>


namespace Ui {
class MySocket;
}

class MySocketHandler;

class MySocket : public QWidget
{
    Q_OBJECT

public:
    explicit MySocket(QWidget *parent = 0);
    ~MySocket();


signals:
    void connect(QString, int);
    void disconnect();
    void sendData(QByteArray);
    void sendValue(double, double, double);
    void disp();

public slots:
    void connected();
    void disconnected();
    void getBuffer(QByteArray);
    void getError(QString);
    void getValue(double, double, double);

private slots:
    void on_send_clicked();
    void on_connect_clicked();

    void on_pushButton_clicked();

private:
    Ui::MySocket *ui;
    MySocketHandler *socketHandler;
};

#endif // MYSOCKET_H
