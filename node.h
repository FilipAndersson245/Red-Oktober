#ifndef NODE_H
#define NODE_H
#include "gridobject.h"
#include "dirconnections.h"

class Node : public GridObject
{
public:
    Node();
    void paintMember(QPainter &painter);

    //wip
    void connectNodes(Direction side,Node* nodePtr);
    void disconnectNodes(Direction side);
private:
    DirConections _connectionHandler;
};

#endif // NODE_H
