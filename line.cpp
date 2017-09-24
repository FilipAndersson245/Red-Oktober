#include "line.h"

Line::Line(int x, int y, Orientation orientation, QPoint point, int size, Node* conn1, Node* conn2): GridObject(x, y)
{
    _firstConnection = conn1;
    _secondConnection = conn2;

    _pos = point;
    _orientation = orientation;
    _gridSize = size;

    //create shapes
    this->setRect(_pos.x(), _pos.y(), size, size);
    QBrush brush(Qt::transparent);
    this->setBrush(brush);
    QPen pen(Qt::transparent);
    this->setPen(pen);
    _itemGroup = new QGraphicsItemGroup(this);
    QBrush brush2(Qt::black);
    QPen pen2(Qt::black);

    //set orientation
    switch(_orientation)
    {
    case Orientation::horizontal:

        _lineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/2), _gridSize, _gridSize/40);
        break;

    case Orientation::vertical:

        _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2), _pos.y(), _gridSize/40, _gridSize);
        break;
    }

    //connect shapes in groups
    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush2);
    _lineRect->setPen(pen2);
}

//emit left or right click function
void Line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clickedLine(this);
    }
    else if (event->button() == Qt::RightButton)
    {
        emit rightClickedLine(this);
    }
}

Orientation Line::getOrientation()
{
    return this->_orientation;
}

Node *Line::getFirstConnection()
{
    return this->_firstConnection;
}

Node *Line::getSecondConnection()
{
    return this->_secondConnection;
}

bool Line::checkIsDouble()
{
    return this->_isDouble;
}

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
            _lineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/2.5), _gridSize, _gridSize/40);
            _secondLineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/1.66), _gridSize, _gridSize/40);
            break;

        case Orientation::vertical:
            _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2.5), _pos.y(), _gridSize/40, _gridSize);
            _secondLineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/1.66), _pos.y(), _gridSize/40, _gridSize);
            break;
    }
    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush);
    _lineRect->setPen(pen);
    _itemGroup->addToGroup(_secondLineRect);
    _secondLineRect->setBrush(brush);
    _secondLineRect->setPen(pen);
}

void Line::removeSecondLine()
{
    _isDouble = false;

    _itemGroup->removeFromGroup(_lineRect);
    _itemGroup->removeFromGroup(_secondLineRect);

    if(this->_secondLineRect != nullptr)
    {
        delete _secondLineRect;
    }
    if(this->_lineRect != nullptr)
    {
        delete _lineRect;
    }

    QBrush brush2(Qt::black);
    QPen pen2(Qt::black);

    switch(_orientation)
    {
        case Orientation::horizontal:
            _lineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/2), _gridSize, _gridSize/40);
            break;
        case Orientation::vertical:
            _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2), _pos.y(), _gridSize/40, _gridSize);
            break;
    }

    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush2);
    _lineRect->setPen(pen2);
}

Line::~Line()
{
    delete _lineRect;
    delete _itemGroup;
}

