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
    std::map<Direction,int> getSlotMap();

    //wip
    int getRemaining();

private:
      const int _maximumConnections;
            int _currentConnections = 0;
    NodeConnect _leftValues = 0;
    NodeConnect _topValues = 0;
    NodeConnect _rightValues = 0;
    NodeConnect _bottomValues = 0;
};
#endif // DIRCONNECTIONS_H
//
