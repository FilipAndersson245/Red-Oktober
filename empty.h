#pragma once

#include "gridobject.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsItemGroup>

class Empty : public GridObject
{

    Q_OBJECT

public:

    Empty(QPoint point, int size);

};
