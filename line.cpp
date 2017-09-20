#include "line.h"

Line::Line(int x, int y, Orientation orientation, QPoint point, int size): GridObject(x, y)
{
    connect(this, SIGNAL(clicked()), this, SLOT(addSecondLine()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(removeSecondLine()));
    _pos = point;
    _orientation = orientation;
    _gridSize = size;
    this->setRect(_pos.x(), _pos.y(), size, size);
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
        _lineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/2), _gridSize, _gridSize/40);
        break;
    }
    case Orientation::vertical:
    {
        _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2), _pos.y(), _gridSize/40, _gridSize);
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

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton && _isDouble)
    {
        emit rightClicked();
    }
    else if (event->button() == Qt::LeftButton && !_isDouble)
    {
        emit clicked();
    }
    else if(event->button() == Qt::RightButton && !_isDouble)
    {
        emit addEmpty(this);
        delete this;
    }
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
    {
        _lineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/2.5), _gridSize, _gridSize/40);
        _secondLineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/1.66), _gridSize, _gridSize/40);
        break;
    }
    case Orientation::vertical:
    {
        _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2.5), _pos.y(), _gridSize/40, _gridSize);
        _secondLineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/1.66), _pos.y(), _gridSize/40, _gridSize);
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
        _lineRect = new QGraphicsRectItem(_pos.x(), _pos.y() + (_gridSize/2), _gridSize, _gridSize/40);
        _itemGroup->addToGroup(_lineRect);
        _lineRect->setBrush(brush2);
        _lineRect->setPen(pen2);
        break;
    }
    case Orientation::vertical:
    {
        _lineRect = new QGraphicsRectItem(_pos.x() + (_gridSize/2), _pos.y(), _gridSize/40, _gridSize);
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

