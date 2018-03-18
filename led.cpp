#include "led.h"
#include "ui_led.h"

#include <QPainter>

LED::LED(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LED)
{
    ui->setupUi(this);
    this->color = Qt::green;
}

LED::~LED()
{
    delete ui;
}


void LED::setColor(QColor color)
{
    this->color = color;
}

void LED::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(width() / 2, height() / 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::transparent);
    painter.fillRect(-width(), -height(), width() * 2, height() * 2, QColor(240, 240, 240));

    int radius = 50;

    // 外边框
    QLinearGradient lg1(0, -radius, 0, radius);
    lg1.setColorAt(0, QColor(255, 255, 255));
    lg1.setColorAt(1, QColor(166, 166, 166));
    painter.setBrush(lg1);
    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);

    // 内边框
    radius -= 13;
    QLinearGradient lg2(0, -radius, 0, radius);
    lg2.setColorAt(0, QColor(166, 166, 166));
    lg2.setColorAt(1, QColor(255, 255, 255));
    painter.setBrush(lg2);
    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);

    radius -= 4;
    QBrush br(this->color);
    painter.setBrush(br);
    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);

}
