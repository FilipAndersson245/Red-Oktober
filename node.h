#ifndef NODE_H
#define NODE_H
#include <time.h>
#include "gridobject.h"

class Node : public GridObject
{
public:

    void paintMember(QPainter &painter);
    int returnRandom(int limit);
    Node(QPoint location);
private:
};

#endif // NODE_H
