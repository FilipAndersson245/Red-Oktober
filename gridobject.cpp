#include "gridobject.h"

GridObject::GridObject(int x, int y):_xVectorPos(x),_yVectorPos(y)
{
    setAcceptHoverEvents(true);
    //qDebug() << "rect created";
}

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
