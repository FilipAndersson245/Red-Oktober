#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H
#include <QPainter>
#include <QPoint>
#include <QPixmap>
class GridObject
{
public:
   GridObject();
   virtual void paintMember(QPainter* painter,int operation = 0) = 0;
   virtual QPoint returnPosition(void) = 0;
   virtual void setMaximumNodeConnections(int newMax) = 0;
   virtual int returnNoOfConnections(void) = 0;
protected:
   int _maxNoOfConnectors;
   QPoint _locationOfNode;
   };

#endif // GRIDOBJECT_H
