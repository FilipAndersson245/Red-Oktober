#include "node.h"
Node::Node()
{
    _value = 1;
}

void Node::paintMember(QPainter &painter)
{

}

void Node::connectNodes(Direction side, Node *nodePtr)
{
    this->_connectionHandler.selectConnection(side)->connect(nodePtr);
}

void Node::disconnectNodes(Direction side)
{
    this->_connectionHandler.selectConnection(side)->disconnect();
}
