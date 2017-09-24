#include "node.h"

Node::Node(int x, int y, int nodeSize, QPoint point, int size): GridObject(x, y),_connectionHandler(nodeSize)
{
    _pos = point;
    this->setRect(_pos.x(), _pos.y(), size, size);
    QBrush brush(Qt::transparent);
    this->setBrush(brush);
    QPen pen(Qt::transparent);
    this->setPen(pen);

    _nodeCircle = new QGraphicsEllipseItem(_pos.x(), _pos.y(), size, size);
    _nodeCircle->setZValue(1000);
    QGraphicsDropShadowEffect * _dropShadow = new QGraphicsDropShadowEffect();
    _dropShadow->setBlurRadius(12);
    _dropShadow->setColor(QColor(0,0,0,200));
    _dropShadow->setOffset(QPoint(2,2));
    _nodeCircle->setGraphicsEffect(_dropShadow);
    QString nodeString = QString::number(nodeSize);
    QFont serifFont("Gill Sans MT", 12);
    _nodeText = new QGraphicsTextItem(nodeString);
    _nodeText->setDefaultTextColor(Qt::white);
    _nodeText->setFont(serifFont);
    _nodeText->setPos(point.x() + (4-_nodeText->boundingRect().width()/8)  , point.y()-7);
    _nodeText->setZValue(1010);
    _nodeText->setAcceptHoverEvents(false);
    _itemGroup = new QGraphicsItemGroup(this);
    _itemGroup->addToGroup(_nodeCircle);
    _itemGroup->addToGroup(_nodeText);
    updateColor();
    _nodeCircle->setPen(pen);
}

void Node::connectNodes(Direction side, Node *nodePtr)
{
    this->_connectionHandler.selectConnection(side)->connect(nodePtr);
}

void Node::addBridge(Direction side)
{
    if(this->_connectionHandler.selectConnection(side)->getAmountOfConnects() < 2)
    {
        this->_connectionHandler.selectConnection(side)->addBridge();
        this->_connectionHandler.setConnections(this->_connectionHandler.getConnections() + 1);
        this->updateColor();
    }
}

void Node::removeBridge(Direction side)
{
    if(this->_connectionHandler.selectConnection(side)->getAmountOfConnects() > 0)
    {
        this->_connectionHandler.selectConnection(side)->removeBridge();
        this->_connectionHandler.setConnections(this->_connectionHandler.getConnections() - 1);
        this->updateColor();
    }
}

int Node::getRemaining()
{
    return this->_connectionHandler.getRemaining();
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
    std::map<Direction, std::vector<GridObject *>> potentialLines = {
        {Direction::top,this->getPotentialLinesDir(Direction::top,board)},
        {Direction::right,this->getPotentialLinesDir(Direction::right,board)},
        {Direction::bottom,this->getPotentialLinesDir(Direction::bottom,board)},
        {Direction::left,this->getPotentialLinesDir(Direction::left,board)},
    };
    return potentialLines;
}

bool Node::isHovered()
{
    return _nodeCircle->isUnderMouse();
}

std::map<Direction, Node *> Node::getConnectedNodes()
{

    std::map<Direction, Node *> nodeMap = {
        {Direction::top,this->_connectionHandler.selectConnection(Direction::top)->getTarget()},
        {Direction::right,this->_connectionHandler.selectConnection(Direction::right)->getTarget()},
        {Direction::bottom,this->_connectionHandler.selectConnection(Direction::bottom)->getTarget()},
        {Direction::left,this->_connectionHandler.selectConnection(Direction::left)->getTarget()}
    };
    return nodeMap;
}

void Node::updateColor()
{
    QColor mycolor;
    int connectionLeft = this->_connectionHandler.getRemaining();
    int H = 232;
    int S = int((14 + (8*connectionLeft)) * 2.55);
    int L = int((77 - (6.875*connectionLeft)) * 2.55);
    mycolor.setHsl(H,S,L);
    if(connectionLeft == 0)
    {
        mycolor.setHsl(123, int(60*2.55), int(62*2.55));
    }
    else if(connectionLeft < 0 || connectionLeft > (this->_connectionHandler.getRemaining() + this->_connectionHandler.getConnections()))
    {
        //debugging for wrong value
        mycolor.setRgb(255,0,0);
    }
    _nodeCircle->setBrush(QBrush(mycolor));
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit mouseEnter(this);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit mouseLeave(this);
}


std::vector<GridObject *> Node::getPotentialLinesDir(Direction direction, std::vector<std::vector<GridObject *> > *board)
{
    std::vector<GridObject *> potentialLines;

    switch(direction)
    {
        case Direction::right:
            if(this->_connectionHandler.selectConnection(Direction::right)->getTarget() != nullptr)
            {
                for(int i = this->getXPos() + 1 ;i < this->_connectionHandler.selectConnection(Direction::right)->getTarget()->getXPos();i++)
                {
                    potentialLines.push_back(board[0][i][this->getYPos()]);
                }
            }
            break;

        case Direction::left:
            if(this->_connectionHandler.selectConnection(Direction::left)->getTarget() != nullptr)
            {
                for(int i = this->getXPos() - 1 ;i > this->_connectionHandler.selectConnection(Direction::left)->getTarget()->getXPos();i--)
                {
                    potentialLines.push_back(board[0][i][this->getYPos()]);
                }
            }
            break;


        case Direction::bottom:
            if(this->_connectionHandler.selectConnection(Direction::bottom)->getTarget() != nullptr)
            {
                for(int i = this->getYPos() + 1 ;i < this->_connectionHandler.selectConnection(Direction::bottom)->getTarget()->getYPos(); i++)
                {
                    potentialLines.push_back(board[0][this->getXPos()][i]);
                }
            }
            break;

        case Direction::top:
            if(this->_connectionHandler.selectConnection(Direction::top)->getTarget() != nullptr)
            {
                for(int i = this->getYPos() - 1 ;i > this->_connectionHandler.selectConnection(Direction::top)->getTarget()->getYPos(); i--)
                {
                    potentialLines.push_back(board[0][this->getXPos()][i]);
                }
            }
            break;
    }
    return potentialLines;
}
