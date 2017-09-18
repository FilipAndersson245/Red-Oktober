#include "dirconnections.h"

DirConections::DirConections(int size): _maximumConnections(size)
{
    this->_DirConections = {
        {Direction::top, NodeConnect()},
        {Direction::right, NodeConnect()},
        {Direction::bottom, NodeConnect()},
        {Direction::left, NodeConnect()},
    };
}

NodeConnect *DirConections::selectConnection(Direction direction)
{
    return &this->_DirConections[direction];

}

std::map<Direction,int> DirConections::getSlotMap()
{
    std::map<Direction,int> freeSlots;
    freeSlots = {
        {Direction::top,this->_DirConections[Direction::top].getAmountOfConnects()},
        {Direction::right,this->_DirConections[Direction::right].getAmountOfConnects()},
        {Direction::bottom,this->_DirConections[Direction::bottom].getAmountOfConnects()},
        {Direction::left,this->_DirConections[Direction::left].getAmountOfConnects()},
    };
    return freeSlots;
}

int DirConections::getRemaining()
{
    return this->_maximumConnections - this->_currentConnections;
}

std::vector<GridObject *> DirConections::getPotentialLinesDir(Direction direction, std::vector<std::vector<GridObject *> > *board, Node *node)
{
    std::vector<GridObject *> potentialLine;
    this->_DirConections[direction]


            return potentialLine;
}

QPoint DirConections::getIndexFromBoard(std::vector<std::vector<GridObject *> > *board, Node *node)
{
    for(int x = 0; x<board->size();x++)
    {
        for(int y = 0; y<board[x].size();y++)
        {
            if(board[x][y] == node)
            {
                return QPoint(x,y);
            }
        }
    }
}

