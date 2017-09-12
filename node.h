#pragma once

#include "gridobject.h"
#include "dirconnections.h"


class Node : public GridObject
{
public:

    Node(int size);

    void paintMember(QPainter &painter);

    //wip
    void connectNodes(Direction side,Node* nodePtr);

    void disconnectNodes(Direction side);

    std::map<Direction,int> getSlotMap();

    void paint();

private:

    DirConections _connectionHandler;

};
