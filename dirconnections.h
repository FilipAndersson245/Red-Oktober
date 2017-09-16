#ifndef DIRCONNECTIONS_H
#define DIRCONNECTIONS_H
#include "nodeconnect.h"
#include <map>
#include <vector>

//
#include<gridobject.h>

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
    std::vector<GridObject *> getPotentialLinesDir(Direction direction,std::vector<std::vector<GridObject*>> *board,Node * node);



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
