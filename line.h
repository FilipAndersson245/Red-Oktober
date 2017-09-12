#pragma once

#include "gridobject.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#define WINDOWSIZE 200

class Line : public GridObject
{
public:

    Line(bool vertical);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addSecondLine();

    void removeLine();

    void rectClicked();

private:

    bool _isVertical = 0;

    bool _isDouble = 0;

};

