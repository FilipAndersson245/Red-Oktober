#include "node.h"
#define SIZEOFNODEPAINTED 40
#define MINDISTANCE 10
Node::Node(QPoint aLocation)
{
    _maxNoOfConnectors = 1 + returnRandom(5);
    _locationOfNode = aLocation;

}


// to be implemented //
void Node::paintMember(QPainter *painter,int operation)
{
QString noOfNodes = "0";
noOfNodes = QString::number(_maxNoOfConnectors);
 painter->setBrush(QBrush(Qt::blue));
    painter->drawEllipse(_locationOfNode.x(),_locationOfNode.y(),SIZEOFNODEPAINTED,SIZEOFNODEPAINTED);
  painter->setBrush(QBrush(Qt::green));
    painter->drawText(_locationOfNode.x()+SIZEOFNODEPAINTED/2,_locationOfNode.y()+SIZEOFNODEPAINTED/2,noOfNodes);
    // painter->drawPixmap(_locationOfNode.x(),_locationOfNode.y(),SIZEOFNODEPAINTED,SIZEOFNODEPAINTED,_picture);
}

void Node::setMaximumNodeConnections(int newMax)
{
    _maxNoOfConnectors = newMax;
}

int Node::returnNoOfConnections()
{
    return _maxNoOfConnectors;
}


QPoint Node::returnPosition(void)
{
    return _locationOfNode;
}

int Node::returnRandom(int limit)
{
    return rand() % limit;

    std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());     // provide seed

    std::uniform_int_distribution<int> uid{ 1,limit };   // help dre to generate nos from 0 to lim (lim included);
    return uid(dre);    // pass dre as an argument to uid to generate the random no

}
