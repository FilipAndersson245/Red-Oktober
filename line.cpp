#include "line.h"

Line::Line(bool vertical)
{
    _lineRect = new QGraphicsRectItem(_xPos, _yPos, WINDOWSIZE/GAMEGRIDSIZE/20, WINDOWSIZE/GAMEGRIDSIZE);
    _itemGroup = new QGraphicsItemGroup(this);
    _itemGroup->addToGroup(_lineRect);

    _isVertical = vertical;
    if (_isVertical)
    {

    }
    else
    {

    }
    qDebug() << "line created";
}
/*
void Line::setPos(int xPos, int yPos)
{

}
*/
void Line::addSecondLine()
{

}

void Line::removeLine()
{
    this->removeLine();
}

