#include "gridobject.h"

GridObject::GridObject(int x, int y):_xVectorPos(x),_yVectorPos(y)
{
    setAcceptHoverEvents(true);
    //qDebug() << "rect created";
}

/*
void GridObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}
*/

void GridObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEnter(this);
}


void GridObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverLeft(this);
}


int GridObject::getXPos()
{
    return _xVectorPos;
}

int GridObject::getYPos()
{
    return _yVectorPos;
}

GridObject::~GridObject()
{

}

void GridObject::setPotentialLine(bool value)
{
    this->_isPotentialLine = value;
}

bool GridObject::isPotentialLine()
{
    return this->_isPotentialLine;
}

/*
void GridObject::rectClicked()
{
    QBrush brush(Qt::red);
    this->setBrush(brush);
    qDebug() << "rect clicked";
    _alreadyClicked = true;
}
*/
/*
void GridObject::rectEntered()
{

    if(!_alreadyClicked)
    {
        QBrush brush(Qt::lightGray);
        this->setBrush(brush);
    }

}
*/
/*
void GridObject::rectLeft()
{
    if(!_alreadyClicked)
    {
        QBrush brush(Qt::transparent);
        this->setBrush(brush);
    }
}
*/
