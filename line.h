#pragma once

#include "gridobject.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>

#define GAMEGRIDSIZE 10
#define WINDOWSIZE 200
class Line : public GridObject
{

    Q_OBJECT

public:
    Line(Orientation orientation, QPoint point, int size, GridObject* node1Connected, GridObject* node2Connected);
    QPoint returnPosition(void)override;
    void setMaximumNodeConnections(int newMax)override;
    int returnNoOfConnections(void)override;
    int getType(void)override;
    void toggleClickedColor(bool onOff)override;
    bool isInside(QPoint pointToCheck)override;
    void setPos(QPoint newPos)override;
    void connectNode(GridObject* node)override;
    bool hasConnectionWith(GridObject* node)override;
    bool hasExceededConnectionLimit(GridObject* node)override;
    void toggleDoubleLine(void) override;
    void disconnectNode(GridObject* node);
    void disconnectLine();
    Orientation getLineOrientation(void);
   // void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    ~Line();

public slots:

    void addSecondLine();

    void removeSecondLine();

signals:

    //void clicked();

    void rightClicked();

    void addEmpty(Line*);

private:

    bool _isDouble = false;

    Orientation _orientation;

    QGraphicsRectItem *_lineRect;

    QGraphicsRectItem *_secondLineRect;

    int _gridSize;

    GridObject* _node1Connected;
    GridObject* _node2Connected;
};

