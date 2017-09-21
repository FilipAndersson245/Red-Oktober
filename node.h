#pragma once

#include "gridobject.h"
#include "dirconnections.h"


class Node : public GridObject
{

    Q_OBJECT



public:

    Node(int x, int y, int nodeSize, QPoint point, int size);

    void paintMember(QPainter &painter);

    //wip
    void connectNodes(Direction side,Node* nodePtr);

    void addBridge(Direction side);

    void removeBridge(Direction side);

    std::map<Direction,int> getSlotMap();

    bool isFull();

    void paint();

    int getRemaining();

    std::map<Direction, std::vector<GridObject *> > getAllPotentialLines(std::vector<std::vector<GridObject*>> *board);

    bool isHovered();

    std::map<Direction, Node *> getConnectedNodes();

    void updateColor();


    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

signals:

    void mouseEnter(Node*);

    void mouseLeave(Node*);

private:

    std::vector<GridObject *> getPotentialLinesDir(Direction direction,std::vector<std::vector<GridObject*>> *board);

    DirConections _connectionHandler;

    QGraphicsEllipseItem *_nodeCircle;

    QGraphicsTextItem *_nodeText;

};
