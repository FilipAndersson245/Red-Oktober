#include "node.h"

Node::Node(int x, int y, int nodeSize, QPoint point, int size):_connectionHandler(size), GridObject(x, y)
{
    _pos = point;
    this->setRect(_pos.x(), _pos.y(), size, size);
    QBrush brush(Qt::transparent);
    this->setBrush(brush);
    QPen pen(Qt::transparent);
    this->setPen(pen);
    _nodeCircle = new QGraphicsEllipseItem(_pos.x(), _pos.y(), size, size);
    QString nodeString = QString::number(nodeSize);
    _nodeText = new QGraphicsTextItem(nodeString);
    _nodeText->setPos(point.x() + size/6, point.y() - size/10);
    _itemGroup = new QGraphicsItemGroup(this);
    _itemGroup->addToGroup(_nodeCircle);
    _itemGroup->addToGroup(_nodeText);
    QBrush brush2(Qt::cyan);
    QPen pen2(Qt::darkBlue);
    _nodeCircle->setBrush(brush2);
    _nodeCircle->setPen(pen2);
}

void Node::connectNodes(Direction side, Node *nodePtr)
{
    this->_connectionHandler.selectConnection(side)->connect(nodePtr);
}

void Node::addBridge(Direction side)
{
    this->_connectionHandler.selectConnection(side)->addBridge();
}

void Node::removeBridge(Direction side)
{
    this->_connectionHandler.selectConnection(side)->removeBridge();
}

int Node::getRemaining()
{
    this->_connectionHandler.getRemaining();
}

std::map<Direction, int> Node::getSlotMap()
{
    return this->_connectionHandler.getSlotMap();
}

bool Node::isFull()
{
    if(this->_connectionHandler.getRemaining()==0) return true;
    return false;
}

std::map<Direction, std::vector<GridObject *> > Node::getAllPotentialLines(std::vector<std::vector<GridObject *> > *board)
{
    //todo functions
    std::map<Direction, std::vector<GridObject *>> potentialLines = {
        {Direction::top,this->getPotentialLinesDir(Direction::top,board)},
        {Direction::right,this->getPotentialLinesDir(Direction::right,board)},
        {Direction::bottom,this->getPotentialLinesDir(Direction::bottom,board)},
        {Direction::left,this->getPotentialLinesDir(Direction::left,board)},
    };

    int a = 5;
    return potentialLines;
}

bool Node::isHovered()
{
    return _nodeCircle->isUnderMouse();
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit mouseEnter(this);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

}


std::vector<GridObject *> Node::getPotentialLinesDir(Direction direction, std::vector<std::vector<GridObject *> > *board)
{
    std::vector<GridObject *> potentialLines;

    switch(direction)
    {
        case Direction::right:
            for(int i = this->getXPos() + 1 ;i < this->_connectionHandler.selectConnection(Direction::right)->getTarget()->getXPos();i++)
            {
                potentialLines.push_back(board[0][i][this->_pos.y()]);
            }
            break;

        case Direction::left:
            for(int i = this->getXPos() - 1 ;i > this->_connectionHandler.selectConnection(Direction::left)->getTarget()->getXPos();i--)
            {
                potentialLines.push_back(board[0][i][this->getYPos()]);
            }
            break;


        case Direction::bottom:
            for(int i = this->getYPos() + 1 ;i < this->_connectionHandler.selectConnection(Direction::bottom)->getTarget()->getYPos(); i++)
            {
                if()
                potentialLines.push_back(board[0][this->getXPos()][i]);
            }
            break;

        case Direction::top:
            for(int i = this->getYPos() - 1 ;i > this->_connectionHandler.selectConnection(Direction::top)->getTarget()->getYPos(); i--)
            {
                potentialLines.push_back(board[0][this->getXPos()][i]);
            }
            break;
    }

    int a = 5;
    return potentialLines;
}
