#include "gridobject.h"

GridObject::GridObject()
{
    connect(this, SIGNAL(clicked()), this, SLOT(rectClicked()));
}

void GridObject::setPos(int xPos, int yPos)
{
    _xPos = xPos;
    _yPos = yPos;
    this->setRect(_xPos, _yPos, WINDOWSIZE/GAMEGRIDSIZE, WINDOWSIZE/GAMEGRIDSIZE);
}

void GridObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}


GridObject::~GridObject()
{
    delete this;
}

void GridObject::rectClicked()
{

}
