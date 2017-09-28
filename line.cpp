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
    QBrush brush2(QColor(88,88,88));
    QPen pen2(QColor(88,88,88));

    //set orientation
    switch(_orientation)
    {
    case Orientation::horizontal:

        _lineRect = new QGraphicsRectItem(_pos.x() - (_gridSize/5), _pos.y() + (_gridSize/2), _gridSize * 1.4, _gridSize/15);
        break;

    case Orientation::vertical:

        _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2.1), _pos.y() - (_gridSize/5), _gridSize/15, _gridSize * 1.4);
        break;
    }

    //connect shapes in groups
    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush2);
    _lineRect->setPen(pen2);
    _lineRect->setAcceptHoverEvents(false);
    this->setZValue(0);
}

//Emit left or right click function to call slot in GameLogic class
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

//Get horizontal or vertical
Orientation Line::getOrientation()
{
    return this->_orientation;
}

//Return the first node this line is connected to
Node *Line::getFirstConnection()
{
    return this->_firstConnection;
}

//Return the second node this line is connected to
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

    QBrush brush(QColor(88,88,88));
    QPen pen(QColor(88,88,88));

    switch(_orientation)
    {
        case Orientation::horizontal:
            _lineRect = new QGraphicsRectItem(_pos.x() - (_gridSize/5), _pos.y() + (_gridSize/2.5), _gridSize * 1.4, _gridSize/15);
            _secondLineRect = new QGraphicsRectItem(_pos.x() - (_gridSize/5), _pos.y() + (_gridSize/1.66), _gridSize * 1.4, _gridSize/15);
            break;

        case Orientation::vertical:
            _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2.5), _pos.y() - (_gridSize/5), _gridSize/15, _gridSize * 1.4);
            _secondLineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/1.66), _pos.y() - (_gridSize/5), _gridSize/15, _gridSize * 1.4);
            break;
    }
    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush);
    _lineRect->setPen(pen);
    _itemGroup->addToGroup(_secondLineRect);
    _secondLineRect->setBrush(brush);
    _secondLineRect->setPen(pen);
    _lineRect->setAcceptHoverEvents(false);
    _secondLineRect->setAcceptHoverEvents(false);
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

    QBrush brush2(QColor(88,88,88));
    QPen pen2(QColor(88,88,88));

    switch(_orientation)
    {
        case Orientation::horizontal:
            _lineRect = new QGraphicsRectItem(_pos.x() - (_gridSize/5), _pos.y() + (_gridSize/2), _gridSize * 1.4, _gridSize/15);
            break;
        case Orientation::vertical:
            _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2.1), _pos.y() - (_gridSize/5), _gridSize/15, _gridSize * 1.4);
            break;
    }

    _itemGroup->addToGroup(_lineRect);
    _lineRect->setBrush(brush2);
    _lineRect->setPen(pen2);
    _lineRect->setAcceptHoverEvents(false);
}

Line::~Line()
{
    delete _lineRect;
}

