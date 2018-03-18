#ifndef MYSOCKETHANDLER_H
#define MYSOCKETHANDLER_H

#include <QObject>
#include <QThread>
#include "tcpsocket.h"
#include "mysocket.h"

class MySocket;

class MySocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit MySocketHandler(MySocket *parent);
    ~MySocketHandler();

signals:
    void cnt(QString, int);
    void send(QByteArray);
    void dcnt();



private:
    TcpSocket *tcpsocket;
    QThread *th;
    MySocket *m_parent;
};

#endif // MYSOCKETHANDLER_H
