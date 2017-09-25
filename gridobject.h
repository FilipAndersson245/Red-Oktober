#pragma once

#define WINDOWSIZE 200

#include <QGraphicsItem>
#include <QObject>
#include <QBrush>
#include <QPen>
#include <QHoverEvent>
#include <QDebug>
#include <QGraphicsItemGroup>

class GridObject : public QObject, public QGraphicsRectItem
{

    Q_OBJECT

public:

    GridObject(int x, int y);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    int getXPos();

    int getYPos();

    virtual ~GridObject();

    void setPotentialLine(bool value);

    bool isPotentialLine();

signals:

    void hoverEnter(GridObject*);

    void hoverLeft(GridObject*);

protected:

    QPoint _pos;

    bool _alreadyClicked = false;

    QGraphicsItemGroup *_itemGroup;

    int _xVectorPos ;

    int _yVectorPos;

    bool _isPotentialLine = false;

};
