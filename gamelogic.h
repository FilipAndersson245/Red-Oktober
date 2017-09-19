#ifndef GAMELOGIC_H
#define GAMELOGIC_H
// includes //
#include <vector>
#include "gridobject.h"
#include "line.h"
#include "node.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <iostream>
#include <fstream>
#include <QFile>
#include <math.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

// defines //

using namespace std;
class GameLogic
{
public:
    GameLogic();

    void addNodeToGameObjects(void);

    vector<vector<GridObject*> > getGameVector(void);
    void loadGameBoardFromFile(QString pathToBoard);
    void setUpNodesWithFileInfo(QByteArray infoFromFile);
    void loadLevel(QByteArray infoFromFile);
    void addGraphicObjects(QGraphicsScene *aScene);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool tryConnection(GridObject *firstNode, GridObject *secondNode, bool isRightClick);


    QPoint computeClick(QPoint position, QGraphicsScene *aScene, bool isRightClick);
private:
    vector<vector<GridObject*> > _allGameObjects;

    GridObject* _firstChoosenNode;
    GridObject* _secondChoosenNode;
};

#endif // GAMELOGIC_H
