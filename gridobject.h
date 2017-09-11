#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H
#include <QPainter>
#include <QPoint>
class GridObject
{
public:
   GridObject();
   virtual void paintMember(QPainter &painter) = 0;
private:
   int _maxNodeConnectors = 0;

};

#endif // GRIDOBJECT_H
