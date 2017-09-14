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
// defines //

using namespace std;
class GameLogic
{
public:
    GameLogic();
    void addNodeToGameObjects(void);
    QPoint returnPosition(int index);
    void paintAll(QPainter* painthere);
    bool setNodeConnection(QPoint firstNodeVectorPos, QPoint secondVectorPos);
    QPoint isCloseToNode(QPoint position);
    vector<vector<GridObject*> > getGameVector(void);
private:
    vector<vector<GridObject*> > _allGameObjects;
};

#endif // GAMELOGIC_H
