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

bool Node::isFull()
{
    if(this->_connectionHandler.getRemaining()==0) return true;
    return false;
}

int Node::getRemaining()
{
    this->_connectionHandler.getRemaining();
}

std::map<Direction, std::vector<GridObject *> > Node::getAllPotentialLines(std::vector<std::vector<GridObject *> > *board)
{
    //todo functions
    std::map<Direction, std::vector<GridObject *>> potentialLines = {
        {Direction::top,this->_connectionHandler.getPotentialLinesDir(Direction::top,board,this)},
        {Direction::top,this->_connectionHandler.getPotentialLinesDir(Direction::right,board,this)},
        {Direction::top,this->_connectionHandler.getPotentialLinesDir(Direction::bottom,board,this)},
        {Direction::top,this->_connectionHandler.getPotentialLinesDir(Direction::left,board,this)},
    };
        return potentialLines;
}
