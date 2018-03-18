#ifndef MYGRAPHSTREAM_H
#define MYGRAPHSTREAM_H

#include<QVector>


class MyGraphStream
{
public:
    MyGraphStream(int max_size);


    void enqueue(double);
    double dequeue();
    QVector<double> buf;

private:
    const int MAX_BUF;
    int count;

};

#endif // MYGRAPHSTREAM_H
