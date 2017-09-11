#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H
#include <QPainter>
#include <QPoint>
class GridObject
{
public:
   GridObject();
   virtual void paintMember(QPainter &painter) = 0;
protected:
   int _maxNoOfConnectors;
   QPoint _locationOfNode;
};

#endif // GRIDOBJECT_H
