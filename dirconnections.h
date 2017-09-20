#pragma once

#include "nodeconnect.h"
#include <map>
#include <vector>

#include <gridobject.h>

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

    int getRemaining();

private:

    const int _maximumConnections;

    int _currentConnections = 0;

    std::map<Direction,NodeConnect> _DirConections;
};

