#include "gridobject.h"

GridObject::GridObject(int x, int y):_xVectorPos(x),_yVectorPos(y)
{
    setAcceptHoverEvents(true);
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
    delete _itemGroup;
}

void GridObject::setPotentialLine(bool value)
{
    this->_isPotentialLine = value;
}

bool GridObject::isPotentialLine()
{
    return this->_isPotentialLine;
}

QPoint GridObject::getPoint()
{
    return _pos;
}
