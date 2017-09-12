#include "node.h"
Node::Node(int size):_connectionHandler(size)
{

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

std::map<Direction, int> Node::getSlotMap()
{
    return this->_connectionHandler.getSlotMap();
}

void Node::paint()
{

}
