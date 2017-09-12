#include "line.h"

Line::Line(bool vertical)
{
    //update();











    _isVertical = vertical;
    if (_isVertical)
    {
        //this->addLine(20, 20, 20, 100, QPen("black"));
    }
    else
    {
        //QLine line = addLine(20, 20, 100, 20, QPen("black"));
    }
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!_isDouble)
    {
        this->setPen(Qt::NoPen);
        this->setBrush(QBrush(QColor(Qt::transparent)));
        painter->drawRect(this->rect());
    }
    else
    {
        this->setBrush(QBrush(QColor(Qt::red)));
        this->setRect(_xPos, _yPos, WINDOWSIZE/GAMEGRIDSIZE, WINDOWSIZE/GAMEGRIDSIZE);
        painter->drawRect(this->rect());
        painter->drawEllipse(this->rect());
    }
}

void Line::addSecondLine()
{

}

void Line::removeLine()
{
    this->removeLine();
}

void Line::rectClicked()
{
    _isDouble = true;
    qDebug("clicked");
    update();
}
