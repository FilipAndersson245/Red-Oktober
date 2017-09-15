#pragma once

#include "gridobject.h"
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

    Line(Orientation orientation, QPoint point, int size);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void removeLine();

public slots:

    void addSecondLine();

    void removeSecondLine();

signals:

    void clicked();

    void rightClicked();

private:

    bool _isDouble = false;

    Orientation _orientation;

    QGraphicsRectItem *_lineRect;

    QGraphicsRectItem *_secondLineRect;

    int _gridSize;
};

