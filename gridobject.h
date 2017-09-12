#pragma once

#define GAMEGRIDSIZE 10
#define WINDOWSIZE 200

#include <QGraphicsItem>
#include <QObject>
#include <QBrush>
#include <QPen>
#include <QPainter>

class GridObject : public QObject, public QGraphicsRectItem
{

    Q_OBJECT

public:

    GridObject();

    void setPos(int xPos, int yPos);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    ~GridObject();

public slots:

    void rectClicked();

signals:

    void clicked();

protected:

    int _xPos;

    int _yPos;
};
