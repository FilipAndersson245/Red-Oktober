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

    GridObject();

    void setPos(int xPos, int yPos);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    ~GridObject();

public slots:

    void rectClicked();

    void rectEntered();

    void rectLeft();

signals:

    void clicked();

    void hoverEnter();

    void hoverLeft();

protected:

    int _xPos;

    int _yPos;

    bool _alreadyClicked = false;

    QGraphicsItemGroup *_itemGroup;
};
