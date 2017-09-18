#include "gridobject.h"

GridObject::GridObject()
{
    setAcceptHoverEvents(true);
    connect(this, SIGNAL(clicked()), this, SLOT(rectClicked()));
    connect(this, SIGNAL(hoverEnter()), this, SLOT(rectEntered()));
    connect(this, SIGNAL(hoverLeft()), this, SLOT(rectLeft()));
    qDebug() << "rect created";
}

void GridObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void GridObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEnter();
}

void GridObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverLeft();
}

GridObject::~GridObject()
{
    delete this;
}

void GridObject::rectClicked()
{
    QBrush brush(Qt::red);
    this->setBrush(brush);
    qDebug() << "rect clicked";
    _alreadyClicked = true;
}

void GridObject::rectEntered()
{

    if(!_alreadyClicked)
    {
        QBrush brush(Qt::lightGray);
        this->setBrush(brush);
    }

}

void GridObject::rectLeft()
{
    /*
    if(!_alreadyClicked)
    {
        QBrush brush(Qt::transparent);
        this->setBrush(brush);
    }
    */
}

