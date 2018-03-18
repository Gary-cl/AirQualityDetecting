#include "tcpsocket.h"
#include <QJsonParseError>
#include <QJsonObject>

TcpSocket::TcpSocket()
{
    QObject::connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(readError()));
    QObject::connect(this, &TcpSocket::readyRead, this, &TcpSocket::readData);
}

TcpSocket::~TcpSocket()
{
    this->abort();
}

void TcpSocket::readData()
{
    QByteArray buffer = this->readAll();

    //解析QJson
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(buffer, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QVariantMap result = parse_doucment.toVariant().toMap();
            if(result.contains("value"))
            {
                QVariantMap val = result["value"].toMap();
                double pm2_5 = val["pm2.5"].toDouble();
                double pm5 = val["pm5"].toDouble();
                double pm10 = val["pm10"].toDouble();

                emit this->sendValue(pm2_5, pm5, pm10);
            }

        }
    }

    emit this->sendBuffer(buffer);
}


void TcpSocket::readError()
{
    QString str = this->errorString();
    emit sendError(str);
}

void TcpSocket::disconnect()
{
    this->disconnectFromHost();
    this->waitForDisconnected(1000);
}

void TcpSocket::connect(QString host, int port)
{
    this->abort();
    this->connectToHost(host,port);
    this->waitForConnected(1000);
}

void TcpSocket::send(QByteArray data)
{
    if (QAbstractSocket::ConnectedState == this->state())
    {
        this->write(data);
    }
}
