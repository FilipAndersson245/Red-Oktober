#include "node.h"
Node::Node(int nodeSize, QPoint point, int size):_connectionHandler(size)
{
    _pos = point;
    this->setRect(_pos.x(), _pos.y(), size, size);
    QBrush brush(Qt::transparent);
    this->setBrush(brush);
    QPen pen(Qt::transparent);
    this->setPen(pen);
    _nodeCircle = new QGraphicsEllipseItem(_pos.x(), _pos.y(), size, size);
    QString nodeString = QString::number(nodeSize);
    _nodeText = new QGraphicsTextItem(nodeString);
    _nodeText->setPos(point.x() + size/6, point.y() - size/10);
    _itemGroup = new QGraphicsItemGroup(this);
    _itemGroup->addToGroup(_nodeCircle);
    _itemGroup->addToGroup(_nodeText);
    QBrush brush2(Qt::cyan);
    QPen pen2(Qt::darkBlue);
    _nodeCircle->setBrush(brush2);
    _nodeCircle->setPen(pen2);
}

void Node::connectNodes(Direction side, Node *nodePtr)
{
    this->_connectionHandler.selectConnection(side)->connect(nodePtr);
}

void Node::disconnectNodes(Direction side)
{
    this->_connectionHandler.selectConnection(side)->disconnect();
}

std::map<Direction, int> Node::getSlotMap()
{
    return this->_connectionHandler.getSlotMap();
}

bool Node::isHovered()
{
   return _nodeCircle->isUnderMouse();
}
