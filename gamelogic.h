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
#define LINE -1
#define EMPTY 0

using namespace std;
class GameLogic : public QObject
{

    Q_OBJECT

public:

    GameLogic(int size);

    void addNodeToGameObjects(void);

    void loadGameBoardFromFile(QString pathToBoard);

    void loadLevel(QByteArray infoFromFile);

    void addGameGraphics(QGraphicsScene* aScene);

    void endGame();

public slots:

    void clickedLine(Line *line);

    void rightClickedLine(Line *line);

    void clickedEmpty(Empty *empty);


    void enterMouseGridObj(GridObject *gridObj);

    void exitMouseGridObj(GridObject *gridObj);


    void enterMouseNode(Node *node);

    void exitMouseNode(Node *node);

private:

    int _gameGridSize;

    void connectNodes(QByteArray infoFromFile,vector<vector<GridObject*>> board);

    void updateHighlighted();

    void clearHighlighted();

    void activateDirection(Direction direction);

    void emptyToLine(Empty *empty, Node *conn1, Node *conn2);

    void linetoEmpty(Line *line);

    static bool isDirectionOrientationAligned(Direction, Orientation);

    void enterMouseGridObjLine(GridObject *gridObj);

    void updateCurrentDirection(GridObject *gridObj);

    bool isGameFinished();

    QPoint _activeNodeCoords;

    Node * _activeNode;

    Direction _currentDirection;

    std::map<Direction, std::vector<GridObject *> > _highLightedObjects;

    vector<vector<GridObject*> > _allGameObjects;

    QGraphicsScene *_gameScene;

    bool _won;

    vector<vector<int>> _gridTypeIndicator; //0 = empty, positive = node, negative = line
};
