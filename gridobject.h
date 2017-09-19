#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H
#include <QPainter>
#include <QPoint>
#include <QPixmap>
#include <QGraphicsItem>
enum class Orientation
{
    horizontal = 0, vertical
};
class GridObject: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:

   GridObject();

   virtual QPoint returnPosition(void) = 0;
   virtual void setMaximumNodeConnections(int newMax) = 0;
   virtual int returnNoOfConnections(void) = 0;
   virtual int getType(void) = 0;
   virtual void toggleClickedColor(bool onOff) = 0;
   virtual bool isInside(QPoint pointToCheck) = 0;
   virtual void setPos(QPoint newPos)=0;
   virtual void connectNode(GridObject* node) = 0;
   virtual bool hasConnectionWith(GridObject* node) = 0;
   virtual bool hasExceededConnectionLimit(GridObject* node) = 0;
   virtual void toggleDoubleLine(void) = 0;
   virtual Orientation getLineOrientation(void) = 0;
   virtual void disconnectNode(GridObject* node) = 0;
protected:
   int _maxNoOfConnectors;
   QPoint _locationOfNode;
   bool _isClicked = false;
   QGraphicsItemGroup *_itemGroup;
   bool _isMarkedForDeletion;
   int _type;
   };

#endif // GRIDOBJECT_H
