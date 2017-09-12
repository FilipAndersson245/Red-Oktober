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
protected:
   int _maxNoOfConnectors;
   QPoint _locationOfNode;
   QPixmap _picture;
};

#endif // GRIDOBJECT_H
