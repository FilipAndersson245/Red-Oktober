#include "node.h"
#define SIZEOFNODEPAINTED 20
#define MINDISTANCE 10
#define NODEGRAPHICSIZE 20
#define MAGICNUMBER 6
#define MAGICNUMBER2 10
Node::Node(QPoint aLocation, int aType, int aSize)
{
    _locationOfNode = aLocation;
    _type = aType;
    _maxNoOfConnectors = aSize;
    _startSize = aSize;
       this->setRect(_locationOfNode.x(), _locationOfNode.y(), NODEGRAPHICSIZE, NODEGRAPHICSIZE);
       QBrush brush(Qt::transparent);
       this->setBrush(brush);
       QPen pen(Qt::transparent);
       this->setPen(pen);
       _nodeCircle = new QGraphicsEllipseItem(_locationOfNode.x(), _locationOfNode.y(), NODEGRAPHICSIZE, NODEGRAPHICSIZE);
       _nodeText = new QGraphicsTextItem(QString::number(_maxNoOfConnectors));
       _nodeText->setPos(_locationOfNode.x() + NODEGRAPHICSIZE/MAGICNUMBER, _locationOfNode.y() - NODEGRAPHICSIZE/MAGICNUMBER2);
       _itemGroup = new QGraphicsItemGroup(this);
       _itemGroup->addToGroup(_nodeCircle);
       _itemGroup->addToGroup(_nodeText);
       QBrush brush2(Qt::cyan);
       QPen pen2(Qt::darkBlue);
       _nodeCircle->setBrush(brush2);
       _nodeCircle->setPen(pen2);
}

void Node::toggleClickedColor (bool onOff)
{
    switch(onOff)
    {
    case false:
    {
        QBrush brush2(Qt::cyan);
        QPen pen2(Qt::darkBlue);
        _nodeCircle->setBrush(brush2);
        _nodeCircle->setPen(pen2);
        _isClicked = false;
        break;
    }
     case true:
    {

        _nodeCircle->setBrush(QBrush(Qt::green,Qt::SolidPattern));
        _isClicked = true;
        break;
    }
    default:
        {}
    }

}

bool Node::isInside(QPoint pointToCheck)
{
   return this->contains(pointToCheck);
}
int Node::getType(void)
{

    return _type;
}

void Node::setPos(QPoint newPos)
{
    _locationOfNode = newPos;

}

void Node::connectNode(GridObject* node)
{
    this->_nodePointers.push_back(node);
    this->updateMaxNoOfConnectors();
}

void Node::updateMaxNoOfConnectors()
{
    if (_maxNoOfConnectors > 0)
    {
        _maxNoOfConnectors = _startSize - _nodePointers.size();
        this->_nodeText->setPlainText(QString::number(_maxNoOfConnectors));
    }

}
bool Node::hasExceededConnectionLimit(GridObject* node)
{
    int noOfTimes = 0;
    for (int i = 0; i < _nodePointers.size();++i)
    {
        if (_nodePointers[i] == node)
            ++noOfTimes;
    }
    if (noOfTimes == 2)
        return true;
}

void Node::disconnectNode(GridObject *node)
{
    for (int i = 0; i < _nodePointers.size();++i)
    {
        if (_nodePointers[i] == node)
        {
            delete _nodePointers[i];
            _nodePointers[i] = nullptr;
        }
    }
    this->updateMaxNoOfConnectors();
}

Orientation Node::getLineOrientation()
{

}

void Node::toggleDoubleLine()
{

}
bool Node::hasConnectionWith(GridObject *node)
{

    for (int i = 0; i < _nodePointers.size();++i)
    {
        if (_nodePointers[i] == node)
             return true;
    }


}


void Node::setMaximumNodeConnections(int newMax)
{
   // _maxNoOfConnectors += newMax;
   // this->_nodeText->setPlainText(QString::number(_maxNoOfConnectors));
}

int Node::returnNoOfConnections()
{
    return _maxNoOfConnectors;
}


QPoint Node::returnPosition(void)
{
    return _locationOfNode;
}


