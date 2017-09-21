#pragma once

#define GAMEGRIDSIZE 10
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

    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    int getXPos();

    int getYPos();

    virtual ~GridObject();

    void setPotentialLine(bool value);

    bool isPotentialLine();

public slots:

    //void rectClicked();

    //void rectEntered();

    //void rectLeft();

signals:

    //void clicked();

    void hoverEnter(GridObject*);

    void hoverLeft(GridObject*);

protected:

    QPoint _pos;

    bool _alreadyClicked = false;

    QGraphicsItemGroup *_itemGroup;

    int _xVectorPos;

    int _yVectorPos;

    bool _isPotentialLine = false;

};
