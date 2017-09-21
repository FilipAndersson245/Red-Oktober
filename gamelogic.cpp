#include "gamelogic.h"
#define GAMEGRIDSIZE 10
#define DISPLACEMENTX 20
#define  DISPLACEMENTY 20
GameLogic::GameLogic()
{

}

void GameLogic::loadGameBoardFromFile(QString pathToBoard)
{
    QByteArray nodePositionData;
    QByteArray nodePositionDataFormatted;
    QFile boardFile(pathToBoard);
    if (!boardFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw (QString("board info file cant be opened! I looked here: "+pathToBoard));
    }
    else
    {
        while (!boardFile.atEnd())
        {
            nodePositionData.append(boardFile.readLine());
        }
        if (boardFile.atEnd())
        {
            for (int i = 0; i < nodePositionData.length(); ++i)
            {
                if (nodePositionData[i] != '\n')
                {
                    nodePositionDataFormatted.append(nodePositionData[i]);
                }
            }
            boardFile.close();
            if(nodePositionDataFormatted.length() != (GAMEGRIDSIZE*GAMEGRIDSIZE))
            {
                throw (QString("Board file data is wrong/corrupt please fix"));
            }
            else
            {
                loadLevel(nodePositionDataFormatted);
                connectNodes(nodePositionDataFormatted, this->_allGameObjects);
            }
        }
    }
}

void GameLogic::loadLevel(QByteArray infoFromFile)
{
    GridObject* pushThisToVector;
    QPoint passVectorElementIDAsPOS;
    int currentNumber;

    for (int i = 0; i < GAMEGRIDSIZE; ++i)
    {
        vector<GridObject*> temp;
        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            currentNumber = (infoFromFile[(j * GAMEGRIDSIZE) + i]-'0');
            passVectorElementIDAsPOS.setX(i*DISPLACEMENTX);
            passVectorElementIDAsPOS.setY(j*DISPLACEMENTY);
            if(currentNumber == 0)
            {
                pushThisToVector = new Empty(i, j, passVectorElementIDAsPOS, WINDOWSIZE/GAMEGRIDSIZE);
                connect(pushThisToVector, SIGNAL(clickedEmpty(Empty*)), this, SLOT(clickedEmpty(Empty*)));
            }
            else
            {
                pushThisToVector = new Node(i, j, (currentNumber), passVectorElementIDAsPOS, WINDOWSIZE/GAMEGRIDSIZE);
                connect(pushThisToVector, SIGNAL(mouseEnter(Node*)), this, SLOT(enterMouseNode(Node*)));
                connect(pushThisToVector, SIGNAL(mouseLeave(Node*)), this, SLOT(exitMouseNode(Node*)));
            }
            connect(pushThisToVector, SIGNAL(hoverEnter(GridObject*)), this, SLOT(enterMouseGridObj(GridObject*)));
            connect(pushThisToVector, SIGNAL(hoverLeft(GridObject*)), this, SLOT(exitMouseGridObj(GridObject*)));
            temp.push_back(pushThisToVector);
        }
        _allGameObjects.push_back(temp);
    }
}

void GameLogic::addGameGraphics(QGraphicsScene* aScene)
{
    _gameScene = aScene;
    for (int i = 0; i < _allGameObjects.size(); ++i)
    {
        for (int j = 0; j < _allGameObjects.size(); j++)
        {
            aScene->addItem(_allGameObjects[i][j]);
        }
    }
}

void GameLogic::clickedLine(Line *line)
{
    qDebug() << "left";

    if(!line->checkIsDouble())
    {
        for(GridObject * item : _highLightedObjects[_currentDirection])
        {
            if(this->_gridTypeIndicator[item->getXPos()][item->getYPos()] == -1)
            {
                Line * highlightedLine = dynamic_cast<Line *>(item);
                highlightedLine->addSecondLine();
            }
        }
    }

        //linetoEmpty(line);
}

void GameLogic::rightClickedLine(Line *line)
{
    qDebug() << "right";
}

void GameLogic::clickedEmpty(Empty *empty)
{
    if(empty->isPotentialLine())
    {
        vector<GridObject*> directionObjects = _highLightedObjects[_currentDirection];
        for(GridObject * object : directionObjects)
        {
            Node * node1 = _activeNode;
            Node * node2 = _activeNode->getConnectedNodes()[_currentDirection];

            node1->addBridge(_currentDirection);
            node2->addBridge(DirConections::getOppositeDirection(_currentDirection));

            emptyToLine(dynamic_cast<Empty *>(object), node1, node2);


            delete object;
        }
        clearHighlighted();
    }
}

void GameLogic::emptyToLine(Empty *empty, Node* conn1, Node* conn2)
{
    int x = empty->getXPos();
    int y = empty->getYPos();
    QPoint point(x*(WINDOWSIZE/GAMEGRIDSIZE), y*(WINDOWSIZE/GAMEGRIDSIZE));

    Orientation ori;
    if(_currentDirection == Direction::right || _currentDirection == Direction::left)
    {
        ori = Orientation::horizontal;
    }
    else if(_currentDirection == Direction::top || _currentDirection == Direction::bottom)
    {
        ori = Orientation::vertical;
    }

    GridObject* line = new Line(x, y, ori, point, WINDOWSIZE/GAMEGRIDSIZE, conn1, conn2);

    connect(line, SIGNAL(clickedLine(Line*)), this, SLOT(clickedLine(Line*)));
    connect(line, SIGNAL(rightClickedLine(Line*)), this, SLOT(rightClickedLine(Line*)));

    connect(line, SIGNAL(hoverEnter(GridObject*)), this, SLOT(enterMouseGridObj(GridObject*)));
    connect(line, SIGNAL(hoverLeft(GridObject*)), this, SLOT(exitMouseGridObj(GridObject*)));

    _allGameObjects[x][y] = line;
    _gridTypeIndicator[x][y] = -1;
    _gameScene->removeItem(empty);
    _gameScene->addItem(_allGameObjects[x][y]);
}

void GameLogic::linetoEmpty(Line *line)
{
    qDebug() << "tried to remove line";
    int x = line->getXPos();
    int y = line->getYPos();
    QPoint point(x*(WINDOWSIZE/GAMEGRIDSIZE), y*(WINDOWSIZE/GAMEGRIDSIZE));
    GridObject* empty = new Empty(x, y, point, WINDOWSIZE/GAMEGRIDSIZE);
    connect(empty, SIGNAL(clickedEmpty(Empty*)), this, SLOT(clickedEmpty(Empty*)));
    _allGameObjects[x][y] = empty;
    _gameScene->removeItem(line);
    _gameScene->addItem(_allGameObjects[x][y]);
}

bool GameLogic::isDirectionOrientationAligned(Direction dir, Orientation ori)
{
    switch(ori)
    {
    case Orientation::vertical:
        if(dir == Direction::top || dir == Direction::bottom)
        {
            return true;
        }
        else
            return false;
    case Orientation::horizontal:
        if(dir == Direction::right || dir == Direction::left)
        {
            return true;
        }
        else
            return false;
    }
}

void GameLogic::enterMouseGridObj(GridObject *gridObj)
{
    if(this->_gridTypeIndicator[gridObj->getXPos()][gridObj->getYPos()] == -1)  //hover line
    {
        clearHighlighted();
        _highLightedObjects.clear();

        Line * selectedLine = dynamic_cast<Line *>(gridObj);
        selectedLine->setPotentialLine(true);
        Node * firstNode = selectedLine->getFirstConnection();
        Node * secondNode = selectedLine->getSecondConnection();

        for(int i = 0; i < firstNode->getConnectedNodes().size(); i++)
        {
            _currentDirection = static_cast<Direction>(i+1);
            if(firstNode->getConnectedNodes()[_currentDirection] == secondNode)
            {
                vector<GridObject*> directionObjects = firstNode->getAllPotentialLines(&_allGameObjects)[_currentDirection];
                clearHighlighted();
                firstNode->setPotentialLine(true);
                secondNode->setPotentialLine(true);
                for(GridObject* item: directionObjects)
                {
                    _highLightedObjects[_currentDirection].push_back(item);
                    item->setPotentialLine(true);
                }
                updateHighlighted();


                break;
            }
        }
    }
    else if(gridObj->isPotentialLine()) //hover empty
    {


        if(gridObj->getYPos() < _activeNodeCoords.y())  //top
        {
            activateDirection(Direction::top);
        }
        else if(gridObj->getXPos() > _activeNodeCoords.x())  //right
        {
            activateDirection(Direction::right);
        }
        else if(gridObj->getYPos() > _activeNodeCoords.y())  //bottom
        {
            activateDirection(Direction::bottom);
        }
        else if(gridObj->getXPos() < _activeNodeCoords.x())  //left
        {
            activateDirection(Direction::left);
        }

        //qDebug() <<"x: "  << gridObj->getXPos() <<"\ty: " << gridObj->getYPos() <<"\tnode-x: "  << _activeNodeCoords.x() <<"\tnode-y: " << _activeNodeCoords.y();
    }
    else
    {
        clearHighlighted();
        _highLightedObjects.clear();
    }

}

void GameLogic::exitMouseGridObj(GridObject *gridObj)
{

}

void GameLogic::enterMouseNode(Node *node)
{
    _activeNode = node;

    _activeNodeCoords = QPoint(node->getXPos(), node->getYPos());

    clearHighlighted();

    node->setPotentialLine(true);

    for(int i = 0; i < node->getConnectedNodes().size(); i++)
    {
        if(node->getConnectedNodes()[static_cast<Direction>(i+1)] != nullptr)
        {
            node->getConnectedNodes()[static_cast<Direction>(i+1)]->setPotentialLine(true);
        }
    }

    //highlight spaces inbetween
    std::map<Direction, std::vector<GridObject *> > objectsToHighlight = node->getAllPotentialLines(&_allGameObjects);;
    for(int i = 0; i < objectsToHighlight.size(); i++)
    {
        Direction localCurrentDirection = static_cast<Direction>(i+1);
        vector<GridObject *> objectVector = objectsToHighlight[localCurrentDirection];
        vector<GridObject *> objectsToAdd;
        for(GridObject * object : objectVector)
        {

            bool isLine = (this->_gridTypeIndicator[object->getXPos()][object->getYPos()] == -1);

            if(isLine)
            {
                GridObject * selectedObject = this->_allGameObjects[object->getXPos()][object->getYPos()];
                Line * objectToTest = dynamic_cast<Line * >(selectedObject);
                bool isCorrectOrient = this->isDirectionOrientationAligned(localCurrentDirection, objectToTest->getOrientation());

                if(!isCorrectOrient)
                {
                    node->getConnectedNodes()[localCurrentDirection]->setPotentialLine(false);
                    objectsToAdd.clear();
                    break;
                }
            }
            if(object == nullptr)
            {
                break;
            }

            objectsToAdd.push_back(object);
        }

        for(GridObject * object : objectsToAdd)
        {
            object->setPotentialLine(true);
        }

        _highLightedObjects[localCurrentDirection] = objectsToAdd;
    }



    updateHighlighted();
}

void GameLogic::exitMouseNode(Node *node)
{

}

void GameLogic::connectNodes(QByteArray infoFromFile, vector<vector<GridObject *>> board)
{
    for(int x = 0; x<GAMEGRIDSIZE; x++)
    {
        vector<int> tempIntVec;
        for(int y = 0; y<GAMEGRIDSIZE; y++)
        {
            tempIntVec.push_back(infoFromFile[y*GAMEGRIDSIZE + x] - 48);
        }
        _gridTypeIndicator.push_back(tempIntVec);
    }

    for(int x = 0; x<GAMEGRIDSIZE; x++)
    {
        for(int y = 0; y<GAMEGRIDSIZE; y++)
        {
            if(_gridTypeIndicator[x][y] != 0)
            {
                Node * currentNode = dynamic_cast<Node *>(board[x][y]);

                //right
                for(int i = x + 1; i<GAMEGRIDSIZE; i++)
                {
                    if(_gridTypeIndicator[i][y] != 0)
                    {
                        currentNode->connectNodes(Direction::right, dynamic_cast<Node *>(board[i][y]));
                        break;
                    }
                }

                //left
                for(int i = x - 1; i>=0; i--)
                {
                    if(_gridTypeIndicator[i][y] != 0)
                    {
                        currentNode->connectNodes(Direction::left, dynamic_cast<Node *>(board[i][y]));
                        break;
                    }
                }

                //bottom
                for(int i = y + 1; i<GAMEGRIDSIZE; i++)
                {
                    if(_gridTypeIndicator[x][i] != 0)
                    {
                        currentNode->connectNodes(Direction::bottom, dynamic_cast<Node *>(board[x][i]));
                        break;
                    }
                }

                //top
                for(int i = y - 1; i>=0; i--)
                {
                    if(_gridTypeIndicator[x][i] != 0)
                    {
                        currentNode->connectNodes(Direction::top, dynamic_cast<Node *>(board[x][i]));
                        break;
                    }
                }
            }
        }
    }
}

void GameLogic::updateHighlighted()
{

    for (int i = 0; i < _allGameObjects.size(); ++i)
    {
        for (int j = 0; j < _allGameObjects.size(); j++)
        {
            if(_allGameObjects[i][j]->isPotentialLine())
            {
                _allGameObjects[i][j]->setBrush(QBrush(Qt::yellow));
            }
            else
            {
                _allGameObjects[i][j]->setBrush(QBrush(Qt::transparent));
            }
        }
    }
}

void GameLogic::clearHighlighted()
{

    for (int i = 0; i < _allGameObjects.size(); ++i)
    {
        for (int j = 0; j < _allGameObjects.size(); j++)
        {
             _allGameObjects[i][j]->setPotentialLine(false);
        }
    }

    updateHighlighted();
}

void GameLogic::activateDirection(Direction direction)
{
    _currentDirection = direction;
    vector<GridObject*> directionObjects = _highLightedObjects[direction];
    clearHighlighted();
    _activeNode->setPotentialLine(true);
    _activeNode->getConnectedNodes()[direction]->setPotentialLine(true);
    for(GridObject* item: directionObjects)
    {
        item->setPotentialLine(true);
    }
    updateHighlighted();
}
