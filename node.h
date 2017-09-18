#pragma once

#include "gridobject.h"
#include "dirconnections.h"


class Node : public GridObject
{

    Q_OBJECT

public:

    Node(int nodeSize, QPoint point, int size);

    void paintMember(QPainter &painter);

    //wip
    void connectNodes(Direction side,Node* nodePtr);

    void disconnectNodes(Direction side);

    std::map<Direction,int> getSlotMap();

    void paint();



    bool isHovered();
private:

    DirConections _connectionHandler;

    QGraphicsEllipseItem *_nodeCircle;

    QGraphicsTextItem *_nodeText;

};
