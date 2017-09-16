#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H
#include <QPainter>
#include <QPoint>
class GridObject
{
public:
   GridObject();
   virtual void paintMember(QPainter &painter) = 0;

   int getGridX();
   int getGridY();

protected:
   int _gridPosX;
   int _gridPosY;

private:
   int _maxNodeConnectors = 0;

};

#endif // GRIDOBJECT_H
//

