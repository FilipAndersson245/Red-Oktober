#include "dirconnections.h"

DirConnections::DirConnections()
{

}

NodeConnect *DirConections::selectConnection(Direction direction)
{
    switch (direction) {
    case Direction::top:
            return &this->_topValues;
        break;
    default:
        break;
    }
}
