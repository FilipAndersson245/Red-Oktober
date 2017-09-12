#include "dirconnections.h"

DirConections::DirConections(int size): _maximumConnections(size)
{
}

NodeConnect *DirConections::selectConnection(Direction direction)
{
    switch (direction) {
    case Direction::top:
            return &this->_topValues;
        break;
    case Direction::left:
        return &this->_leftValues;
        break;
    case Direction::bottom:
        return &this->_bottomValues;
        break;
    case Direction::right:
        return &this->_rightValues;
    default:
        return nullptr;
        break;
    }
}

std::map<Direction,int> DirConections::checkForFreeSides()
{
    std::map<Direction,int> freeSlots;
    freeSlots = {
        {Direction::top,this->_topValues.getAmountOfConnects()},
        {Direction::right,this->_rightValues.getAmountOfConnects()},
        {Direction::bottom,this->_bottomValues.getAmountOfConnects()},
        {Direction::left,this->_leftValues.getAmountOfConnects()},
    };
    return freeSlots;
}
