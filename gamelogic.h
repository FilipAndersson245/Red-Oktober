#pragma once

// includes //
#include <vector>
#include "gridobject.h"
#include "line.h"
#include "node.h"
#include "empty.h"
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QGraphicsScene>
// defines //

using namespace std;
class GameLogic
{

public:

    GameLogic();

    void addNodeToGameObjects(void);

    void loadGameBoardFromFile(QString pathToBoard);

    void loadLevel(QByteArray infoFromFile);

    vector<vector<GridObject*> > getGameVector(void);

    void addGameGraphics(QGraphicsScene* aScene);
private:

    vector<vector<GridObject*> > _allGameObjects;

    QGraphicsScene *_gameScene;

};
