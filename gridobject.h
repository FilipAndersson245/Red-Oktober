#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H
#include <QPainter>
#include <QPoint>

enum class  ClassTypes{
    empty, line , node
};


class GridObject
{
public:
   GridObject();
   virtual void paintMember(QPainter &painter) = 0;

   int getGridX();
   int getGridY();

   //wip
   virtual ClassTypes getClass() = 0;

protected:
   int _gridPosX;
   int _gridPosY;

private:
   int _maxNodeConnectors = 0;
   //add orientation
   //add flag potentialLine

};

#endif // GRIDOBJECT_H
//

