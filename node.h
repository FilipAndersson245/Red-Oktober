#ifndef NODE_H
#define NODE_H
#include <time.h>
#include "gridobject.h"
#include <qDebug>
#include <vector>

class Node : public GridObject
{
public:
    Node(QPoint location, int aType, int aSize);

    void setCoordinates(QPoint position);
    bool isCloseToNode(QPoint position);
    void setMaximumNodeConnections(int newMax);
    int returnNoOfConnections(void);
    QPoint returnPosition(void);
    int getType();
    void toggleClickedColor(bool onOff);
    bool isInside(QPoint pointToCheck);
    void setPos(QPoint newPos);
    void connectNode(GridObject* node);
    void updateMaxNoOfConnectors();
    bool hasConnectionWith(GridObject* node);
    bool hasExceededConnectionLimit(GridObject* node);
    void disconnectNode(GridObject* node);
    Orientation getLineOrientation(void);
    void toggleDoubleLine(void);
private:
    QGraphicsEllipseItem *_nodeCircle;
    QGraphicsTextItem *_nodeText;
    std::vector<GridObject*>_nodePointers;
    int _startSize;
};

#endif // NODE_H
