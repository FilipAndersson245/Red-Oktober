#ifndef DIRCONNECTIONS_H
#define DIRCONNECTIONS_H
#include "nodeconnect.h"
#include <map>

enum class Direction
{
    none = 0,top,right,bottom,left
};

class DirConections
{
public:
    DirConections(int maxConnections);

    NodeConnect *selectConnection(Direction direction);
    bool checkIfFull();

    //todo
    std::map<Direction,int> getSlotMap();

private:
      const int _maximumConnections;
            int _currentConnections = 0;
    NodeConnect _leftValues;
    NodeConnect _topValues;
    NodeConnect _rightValues;
    NodeConnect _bottomValues;
};
#endif // DIRCONNECTIONS_H
//
