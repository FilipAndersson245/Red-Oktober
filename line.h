#pragma once

#include "gridobject.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsItemGroup>

#define GAMEGRIDSIZE 10
#define WINDOWSIZE 200

class Line : public GridObject
{
public:

    Line(bool vertical);

    //void setPos(int xPos, int yPos);

    void addSecondLine();

    void removeLine();

private:

    bool _isVertical = 0;

    bool _isDouble = 0;

    QGraphicsRectItem *_lineRect;
};

