#pragma once

// includes //
#include <vector>
#include "gridobject.h"
#include "line.h"
#include "node.h"
#include "empty.h"
#include <QDebug>
// defines //

using namespace std;
class GameLogic
{

public:

    GameLogic();

    void addNodeToGameObjects(void);

private:

    vector<vector<GridObject*> > _allGameObjects;

    QGraphicsScene *_gameScene;

};
