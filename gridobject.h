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

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;



    virtual ~GridObject();

public slots:

    void rectClicked();

    void rectEntered();

    void rectLeft();

signals:

    void clicked();

    void hoverEnter();

    void hoverLeft();

protected:

    QPoint _pos;

    bool _alreadyClicked = false;

    QGraphicsItemGroup *_itemGroup;
};
