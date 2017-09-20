#pragma once

#include "gridobject.h"
#include "node.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>

#define GAMEGRIDSIZE 10
#define WINDOWSIZE 200

enum class Orientation
{
    horizontal = 0, vertical
};

class Line : public GridObject
{

    Q_OBJECT

public:

    Line(int x, int y, Orientation orientation, QPoint point, int size);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    ~Line();

public slots:

    void addSecondLine();

    void removeSecondLine();

signals:

    void clicked();

    void rightClicked();

    void addEmpty(Line*);

private:

    Node * _firstConnection;

    Node * _secondConnection;

    bool _isDouble = false;

    Orientation _orientation;

    QGraphicsRectItem *_lineRect;

    QGraphicsRectItem *_secondLineRect;

    int _gridSize;
};

