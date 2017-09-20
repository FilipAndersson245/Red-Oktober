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
#include <QObject>
// defines //

using namespace std;
class GameLogic : public QObject
{

    Q_OBJECT

public:

    GameLogic();

    void addNodeToGameObjects(void);

    void loadGameBoardFromFile(QString pathToBoard);

    void loadLevel(QByteArray infoFromFile);

    void addGameGraphics(QGraphicsScene* aScene);

public slots:

    void emptyToLine(Empty *empty);

    void linetoEmpty(Line *line);

private:

    void connectNodes(QByteArray infoFromFile,vector<vector<GridObject*>> board);



    vector<vector<GridObject*> > _allGameObjects;

    QGraphicsScene *_gameScene;

    vector<vector<int>> _gridTypeIndicator; //0 = empty, positive = node, negative = line
};
