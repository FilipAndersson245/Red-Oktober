#include "nodeconnect.h"

NodeConnect::NodeConnect()
{

}

bool NodeConnect::connect(Node *target)
{
    if(this->_connections<2)
    {

        this->_target = target;
        this->_connections++;
        return true;
    }
    return false;
}

bool NodeConnect::disconnect()
{
    if(this->_connections>1)
    {
        this->_connections--;
        return true;
    }
    else if(this->_connections==1)
    {
        this->_target = nullptr;
        this->_connections--;
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

