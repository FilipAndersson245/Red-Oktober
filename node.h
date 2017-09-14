#ifndef NODE_H
#define NODE_H
#include <time.h>
#include "gridobject.h"
#include <qDebug>
class Node : public GridObject
{
public:

    int returnRandom(int limit);
    Node(QPoint location);
    void paintMember(QPainter *painter,int operation = 0);
    void setCoordinates(QPoint position);
    bool isCloseToNode(QPoint position);
    void setMaximumNodeConnections(int newMax);
    int returnNoOfConnections(void);
    QPoint returnPosition(void);
private:

};

#endif // NODE_H
