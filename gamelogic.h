#ifndef GAMELOGIC_H
#define GAMELOGIC_H
// includes //
#include <vector>
#include "gridobject.h"
#include "line.h"
#include "node.h"
// defines //

using namespace std;
class GameLogic
{
public:
    GameLogic();
    void addNodeToGameObjects(void);
private:
    vector<vector<int> > _allGameObjects;
};

#endif // GAMELOGIC_H
