#ifndef NODE_H
#define NODE_H

#include "gridobject.h"

class Node : public GridObject
{
public:
    Node();
    void paintMember(QPainter &painter);
private:

int _value;
};

#endif // NODE_H
