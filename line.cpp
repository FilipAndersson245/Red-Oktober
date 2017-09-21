#include "line.h"


Line::Line(Orientation orientation, QPoint point, int size, GridObject* aNode1Connected, GridObject* aNode2Connected)
{
    _node1Connected = aNode1Connected;
    _node2Connected = aNode2Connected;
    _type = 0;
    connect(this, SIGNAL(clicked()), this, SLOT(addSecondLine()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(removeSecondLine()));
    _locationOfNode = point;
    _orientation = orientation;
    _gridSize = size;
    this->setRect(_locationOfNode.x(), _locationOfNode.y(), size, size);
    QBrush brush(Qt::transparent);
    this->setBrush(brush);
    QPen pen(Qt::transparent);
    this->setPen(pen);
    _itemGroup = new QGraphicsItemGroup(this);
    QBrush brush2(Qt::black);
    QPen pen2(Qt::black);
    switch(_orientation)
    {
    case Orientation::horizontal:
    {
        _lineRect = new QGraphicsRectItem(_locationOfNode.x(), _locationOfNode.y() + (_gridSize/2), _gridSize, _gridSize/40);
        break;
    }
    case Orientation::vertical:
    {
        _lineRect = new QGraphicsRectItem(_locationOfNode.x() + (_gridSize/2), _locationOfNode.y(), _gridSize/40, _gridSize);
        break;
    }
    default:
    {
        qDebug() << "line has no direction";
        break;
    }
    }
    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush2);
    _lineRect->setPen(pen2);
    qDebug() << "line created";
}

Orientation Line::getLineOrientation()
{
    return this->_orientation;
}

//void Line::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    if(event->button() == Qt::RightButton && _isDouble)
//    {
//        emit rightClicked();
//    }
//    else if (event->button() == Qt::LeftButton && !_isDouble)
//    {
//        //emit clicked();
//    }
//    else if(event->button() == Qt::RightButton && !_isDouble)
//    {
//        emit addEmpty(this);
//        delete this;
//    }
//}

void Line::addSecondLine()
{
    _isDouble = true;
    _itemGroup->removeFromGroup(_lineRect);
    delete _lineRect;
    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    switch(_orientation)
    {
    case Orientation::horizontal:
    {
        _lineRect = new QGraphicsRectItem(_locationOfNode.x(), _locationOfNode.y() + (_gridSize/2.5), _gridSize, _gridSize/40);
        _secondLineRect = new QGraphicsRectItem(_locationOfNode.x(), _locationOfNode.y() + (_gridSize/1.66), _gridSize, _gridSize/40);
        break;
    }
    case Orientation::vertical:
    {
        _lineRect = new QGraphicsRectItem(_locationOfNode.x() + (_gridSize/2.5), _locationOfNode.y(), _gridSize/40, _gridSize);
        _secondLineRect = new QGraphicsRectItem(_locationOfNode.x() + (_gridSize/1.66), _locationOfNode.y(), _gridSize/40, _gridSize);
        break;
    }
    default:
    {
        qDebug() << "line has no direction";
        break;
    }
    }
    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush);
    _lineRect->setPen(pen);
    _itemGroup->addToGroup(_secondLineRect);
    _secondLineRect->setBrush(brush);
    _secondLineRect->setPen(pen);
    qDebug() << "Second line added";
}

void Line::removeSecondLine()
{
    _isDouble = false;
    _itemGroup->removeFromGroup(_lineRect);
    _itemGroup->removeFromGroup(_secondLineRect);
    delete _lineRect;
    delete _secondLineRect;
    QBrush brush2(Qt::black);
    QPen pen2(Qt::black);
    switch(_orientation)
    {
    case Orientation::horizontal:
    {
        _lineRect = new QGraphicsRectItem(_locationOfNode.x(), _locationOfNode.y() + (_gridSize/2), _gridSize, _gridSize/40);
        _itemGroup->addToGroup(_lineRect);
        _lineRect->setBrush(brush2);
        _lineRect->setPen(pen2);
        break;
    }
    case Orientation::vertical:
    {
        _lineRect = new QGraphicsRectItem(_locationOfNode.x() + (_gridSize/2), _locationOfNode.y(), _gridSize/40, _gridSize);
        _itemGroup->addToGroup(_lineRect);
        _lineRect->setBrush(brush2);
        _lineRect->setPen(pen2);
        break;
    }
    default:
    {
        qDebug() << "line has no direction";
        break;
    }
    }
    qDebug() << "Second line removed";
}

Line::~Line()
{
    delete _lineRect;
    delete _itemGroup;

}


QPoint Line::returnPosition()
{

}

void Line::setMaximumNodeConnections(int newMax)
{

}

int Line::returnNoOfConnections()
{

}

int Line::getType()
{
return _type;
}

void Line::toggleClickedColor(bool onOff)
{

}

bool Line::isInside(QPoint pointToCheck)
{
return this->contains(pointToCheck);
}

void Line::setPos(QPoint newPos)
{

}

void Line::connectNode(GridObject *node)
{

}

bool Line::hasConnectionWith(GridObject *node)
{

}

bool Line::hasExceededConnectionLimit(GridObject *node)
{

}

void Line::toggleDoubleLine()
{
    if (_type == 2)
     {
         removeSecondLine();
         _type = 0;
     }
    else if (_type == 0)
    {
        addSecondLine();
        _type = 2;

    }

}

void Line::disconnectNode(GridObject* node)
{

}

void Line::disconnectLine()
{

        _node1Connected->disconnectNode(_node2Connected);
        _node2Connected->disconnectNode(_node1Connected);
        _node2Connected = nullptr;
        _node1Connected = nullptr;

}
