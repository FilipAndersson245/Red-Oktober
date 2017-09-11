#ifndef GAMELOGIC_H
#define GAMELOGIC_H
// includes //
#include <vector>
#include "gridobject.h"
#include "line.h"
#include "node.h"
// defines //


class GameLogic
{
public:
    GameLogic();
private:
    std::vector<GridObject*> _allGameObjects;
};

#endif // GAMELOGIC_H
