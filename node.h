#ifndef NODE_H
#define NODE_H
#include "gridobject.h"
#include "dirconnections.h"


class Node : public GridObject
{
public:
    Node(int size);
    void paintMember(QPainter &painter);

    void connectNodes(Direction side,Node* nodePtr);
    void disconnectNodes(Direction side);
    std::map<Direction,int> getSlotMap();

    //wip
    bool isFull();
    int getRemaining();
    ClassTypes getClass();

    std::map<Direction, std::vector<GridObject *> > getAllPotentialLines(std::vector<std::vector<GridObject*>> *board);

private:
    DirConections _connectionHandler;
};

#endif // NODE_H
//
