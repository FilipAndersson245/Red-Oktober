#include "dirconnections.h"

DirConections::DirConections(int size): _maximumAmountOfBridges(size)
{
    this->_DirConections = {
        {Direction::top, NodeConnect()},
        {Direction::right, NodeConnect()},
        {Direction::bottom, NodeConnect()},
        {Direction::left, NodeConnect()},
    };
}

//return the reverse direction
Direction DirConections::getOppositeDirection(Direction inDir)
{
    switch(inDir)
    {
    case Direction::right:
        return Direction::left;
    case Direction::top:
        return Direction::bottom;
    case Direction::bottom:
        return Direction::top;
    case Direction::left:
        return Direction::right;
    default:
        qDebug() << "getOppositeDirection (direction does not exist)";
        return Direction::none;
    }
}

//return pointer to the side asked for in the parameter
NodeConnect *DirConections::selectConnection(Direction direction)
{
    return &this->_DirConections[direction];

}

//get map with amount of bridges each side has
std::map<Direction,int> DirConections::getSlotMap()
{
    std::map<Direction,int> freeSlots = {
        {Direction::top,this->_DirConections[Direction::top].getAmountOfConnects()},
        {Direction::right,this->_DirConections[Direction::right].getAmountOfConnects()},
        {Direction::bottom,this->_DirConections[Direction::bottom].getAmountOfConnects()},
        {Direction::left,this->_DirConections[Direction::left].getAmountOfConnects()},
    };
    return freeSlots;
}

//get how many bridges left until full
int DirConections::getRemaining()
{
    return this->_maximumAmountOfBridges - this->_currentAmountOfBridges;
}

//set the amount of bridges connected to this node
void DirConections::setConnections(int newVal)
{
    this->_currentAmountOfBridges = newVal;
}

//get amount of bridges connected to the node
int DirConections::getConnections()
{
    return this->_currentAmountOfBridges;
}
