#include "empty.h"

Empty::Empty(int x, int y, QPoint point, int size): GridObject(x, y)
{
    _pos = point;
    this->setRect(_pos.x(), _pos.y(), size, size);
    QBrush brush(Qt::transparent);
    this->setBrush(brush);
    QPen pen(Qt::transparent);
    this->setPen(pen);
    _itemGroup = new QGraphicsItemGroup(this);
}

bool Empty::isUnderMouse()
{

}

void Empty::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "clicked";
    if (event->button() == Qt::LeftButton)
    {
        emit clickedEmpty(this);
    }
}

Empty::~Empty()
{
    delete _itemGroup;
}
