#include "mygraphstream.h"

MyGraphStream::MyGraphStream(int max_size) : MAX_BUF(max_size), count(0)
{

}


void MyGraphStream::enqueue(double dat)
{
    //当size等于MAX_BUF时，入队一个元素，便出队一个元素
    if (this->count >= MAX_BUF)
        this->dequeue();

    this->count++;
    this->buf.push_back(dat);
}

double MyGraphStream::dequeue()
{
    double ret = -1;
    if (!this->buf.isEmpty())
    {
        ret = this->buf.takeFirst();
        this->count--;
    }
    return ret;
}
