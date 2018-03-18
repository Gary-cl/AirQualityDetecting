#include "mysockethandler.h"

MySocketHandler::MySocketHandler(MySocket *parent) : m_parent(parent)
{
    tcpsocket = new TcpSocket;
    th = new QThread;
    tcpsocket->moveToThread(th);


    connect(this, &MySocketHandler::cnt, tcpsocket, &TcpSocket::connect);
    connect(this, &MySocketHandler::send, tcpsocket, &TcpSocket::send);
    connect(this, &MySocketHandler::dcnt, tcpsocket, &TcpSocket::disconnect);

    connect(tcpsocket, &TcpSocket::sendValue, m_parent, &MySocket::getValue);
    connect(tcpsocket, &TcpSocket::sendBuffer, m_parent, &MySocket::getBuffer);
    connect(tcpsocket, &TcpSocket::sendError, m_parent, &MySocket::getError);
    connect(tcpsocket, &TcpSocket::connected, m_parent, &MySocket::connected);
    connect(tcpsocket, &TcpSocket::disconnected, m_parent, &MySocket::disconnected);

    th->start();
}


MySocketHandler::~MySocketHandler()
{
    delete tcpsocket;
    tcpsocket = NULL;

    th->quit();
    th->wait();
    delete th;
    th = NULL;

    m_parent = NULL;
}
