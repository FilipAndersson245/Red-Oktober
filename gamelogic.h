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
    void paintTextures(QPainter* painthere);

private:
    vector<vector<GridObject*> > _allGameObjects;
};

#endif // GAMELOGIC_H
