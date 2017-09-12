#ifndef NODE_H
#define NODE_H
#include "gridobject.h"


enum class Direction
{
    none = 0,top,right,bottom,left
};

//
class dirConections
{
public:
    dirConections(int value);


private:
    nodeConnect _leftValues[2];
    nodeConnect _topValues[2];
    nodeConnect _rightValues[2];
    nodeConnect _bottomValues[2];
};

class nodeConnect
{
public:
    nodeConnect();

private:
    Direction _mySide;
    Direction _targetSide;
    Node* _target;
    Node* _me;
};


class Node : public GridObject
{
public:
    Node();
    void paintMember(QPainter &painter);

    //wip
    void connectNodes(Direction side);
private:

int _value;
};

#endif // NODE_H
