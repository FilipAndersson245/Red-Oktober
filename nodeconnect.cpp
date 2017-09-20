#include "nodeconnect.h"

NodeConnect::NodeConnect()
{

}

void NodeConnect::connect(Node *target)
{
    this->_target = target;
}


bool NodeConnect::addBridge()
{
    if(this->_connections<2)
    {
        this->_connections++;
        return true;
    }
    return false;
}

bool NodeConnect::removeBridge()
{
    if(this->_connections>1)
    {
        this->_connections--;
        return true;
    }
    return false;
}

int NodeConnect::getAmountOfConnects()
{
    return this->_connections;
}

Node *NodeConnect::getTarget()
{
    return this->_target;
}

void NodeConnect::setAmountOfConnects(int amount)
{
    this->_connections = amount;
}

void NodeConnect::setTarget(Node *target)
{
    this->_target = target;
}
