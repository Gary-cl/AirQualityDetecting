#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket();
    ~TcpSocket();

signals:
    void sendError(QString);
    void sendBuffer(QByteArray);
    void sendValue(double, double, double);

public slots:
    void disconnect();
    void connect(QString, int);
    void send(QByteArray);
    void readError();
    void readData();
};

#endif // TCPSOCKET_H
