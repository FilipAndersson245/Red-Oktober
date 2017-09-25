#include "gamelogic.h"

GameLogic::GameLogic():_won(false) {}

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
            if(currentNumber == EMPTY)
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
            temp.insert(temp.begin(), pushThisToVector);
        }
        _allGameObjects.insert(_allGameObjects.begin(), temp);
    }
    qDebug() << "boardLoaded";
}

void GameLogic::addGameGraphics(QGraphicsScene* aScene)
{
    _gameScene = aScene;
    for (size_t i = 0; i < _allGameObjects.size(); ++i)
    {
        for (size_t j = 0; j < _allGameObjects.size(); j++)
        {
            aScene->addItem(_allGameObjects[i][j]);
        }
    }
    qDebug() << "all Scenes added";
}

//left clicked a line
void GameLogic::clickedLine(Line *line)
{
    qDebug() << "leftClick on Line";

    if(line->isPotentialLine() && !line->checkIsDouble())
    {
        //adds double line

        enterMouseGridObjLine(dynamic_cast<GridObject *>(line));

        line->getFirstConnection()->addBridge(_currentDirection);
        line->getSecondConnection()->addBridge(DirConections::getOppositeDirection(_currentDirection));
        for(GridObject * item : _highLightedObjects[_currentDirection])
        {
            if(this->_gridTypeIndicator[item->getXPos()][item->getYPos()] == LINE)
            {
                Line * highlightedLine = dynamic_cast<Line *>(item);
                highlightedLine->addSecondLine();
            }
        }

    }
}

void GameLogic::rightClickedLine(Line *line)
{
    qDebug() << "rightClick on Line";

    Node * firstNode = line->getFirstConnection();
    Node * secondNode = line->getSecondConnection();

    if(line->getYPos() < firstNode->getYPos())  //top
    {
        _currentDirection = Direction::top;
    }
    else if(line->getXPos() > firstNode->getXPos())  //right
    {
        _currentDirection = Direction::right;
    }
    else if(line->getYPos() > firstNode->getYPos())  //bottom
    {
        _currentDirection = Direction::bottom;
    }
    else if(line->getXPos() < firstNode->getXPos())  //left
    {
        _currentDirection = Direction::left;
    }


    firstNode->removeBridge(_currentDirection);
    secondNode->removeBridge(DirConections::getOppositeDirection(_currentDirection));

    //get items between nodes
    //WARNING THIS VECTOR DOES NOT ALWAYS HOLD ITEMS BROOOO (maybe?) vvvvv
    vector<GridObject*> directionObjects = firstNode->getAllPotentialLines(&_allGameObjects)[_currentDirection];

    if(line->checkIsDouble())
    {

        for(GridObject * item : directionObjects)
        {
            if(this->_gridTypeIndicator[item->getXPos()][item->getYPos()] == LINE)
            {
                Line * selectedLine = dynamic_cast<Line *>(item);
                selectedLine->removeSecondLine();
            }
        }
        enterMouseGridObj(dynamic_cast<GridObject *>(line));
    }
    else
    {
        for(GridObject * item : directionObjects)
        {
            if(this->_gridTypeIndicator[item->getXPos()][item->getYPos()] == LINE)
            {
                Line * selectedLine = dynamic_cast<Line *>(item);
                linetoEmpty(selectedLine);
            }
        }
    }
}

//
void GameLogic::clickedEmpty(Empty *empty)
{
    if(empty->isPotentialLine())
    {
        qDebug() << "potential empty clicked";
        vector<GridObject*> directionObjects = _highLightedObjects[_currentDirection];
        Node * node1 = _activeNode;
        Node * node2 = _activeNode->getConnectedNodes()[_currentDirection];

        node1->addBridge(_currentDirection);
        node2->addBridge(DirConections::getOppositeDirection(_currentDirection));

        for(GridObject * object : directionObjects)
        {
            emptyToLine(dynamic_cast<Empty *>(object), node1, node2);
            delete object;
            updateHighlighted();

            this->_won = isGameFinished();
        }
    }
    else
    {
        qDebug() << "non potential empty clicked";
    }
}

//convert empty to a line
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
    else
    {
        qDebug() << "ERR Orientation not set \n setting it to Vertical to prevent random resultat";
        ori = Orientation::vertical;
    }

    GridObject* line = new Line(x, y, ori, point, WINDOWSIZE/GAMEGRIDSIZE, conn1, conn2);

    connect(line, SIGNAL(clickedLine(Line*)), this, SLOT(clickedLine(Line*)));
    connect(line, SIGNAL(rightClickedLine(Line*)), this, SLOT(rightClickedLine(Line*)));

    connect(line, SIGNAL(hoverEnter(GridObject*)), this, SLOT(enterMouseGridObj(GridObject*)));
    connect(line, SIGNAL(hoverLeft(GridObject*)), this, SLOT(exitMouseGridObj(GridObject*)));

    _allGameObjects[x][y] = line;
    _gridTypeIndicator[x][y] = LINE;
    _gameScene->removeItem(empty);
    _gameScene->addItem(_allGameObjects[x][y]);

    if(conn1->isFull() || conn2->isFull())
    {
        qDebug() << "one node is full!";
        clearHighlighted();
    }
    else
    {
        _highLightedObjects.clear();
        _highLightedObjects[_currentDirection].push_back(line);
        line->setPotentialLine(true);
    }
}

//convert line to empty
void GameLogic::linetoEmpty(Line *line)
{
    int x = line->getXPos();
    int y = line->getYPos();
    QPoint point(x*(WINDOWSIZE/GAMEGRIDSIZE), y*(WINDOWSIZE/GAMEGRIDSIZE));
    GridObject* empty = new Empty(x, y, point, WINDOWSIZE/GAMEGRIDSIZE);
    connect(empty, SIGNAL(clickedEmpty(Empty*)), this, SLOT(clickedEmpty(Empty*)));

    connect(empty, SIGNAL(hoverEnter(GridObject*)), this, SLOT(enterMouseGridObj(GridObject*)));
    connect(empty, SIGNAL(hoverLeft(GridObject*)), this, SLOT(exitMouseGridObj(GridObject*)));

    _allGameObjects[x][y] = empty;
    _gridTypeIndicator[x][y] = EMPTY;
    _gameScene->removeItem(line);
    _gameScene->addItem(_allGameObjects[x][y]);
}

//look for alignment between two nodes
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
    if(this->_gridTypeIndicator[gridObj->getXPos()][gridObj->getYPos()] == LINE)  //hover line
    {
        enterMouseGridObjLine(gridObj);
    }
    else if(gridObj->isPotentialLine()) //hover empty
    {
        updateCurrentDirection(gridObj);
    }
    else
    {
        clearHighlighted();
        _highLightedObjects.clear();
    }

}

// remove???
void GameLogic::exitMouseGridObj(GridObject *gridObj)
{

}

void GameLogic::enterMouseNode(Node *node)
{
    if(!node->isFull())
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

            //clears direction if direction's node target is full
            if(node->getConnectedNodes()[localCurrentDirection] != nullptr)
            {
                if(node->getConnectedNodes()[localCurrentDirection]->isFull())
                {
                    objectsToHighlight[localCurrentDirection].clear();
                    node->getConnectedNodes()[localCurrentDirection]->setPotentialLine(false);
                }
            }

            vector<GridObject *> objectVector = objectsToHighlight[localCurrentDirection];
            vector<GridObject *> objectsToAdd;
            for(GridObject * object : objectVector)
            {

                bool isLine = (this->_gridTypeIndicator[object->getXPos()][object->getYPos()] == LINE);

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
}

// remove???
void GameLogic::exitMouseNode(Node *node)
{

}


// CRAZY FUNCTION!!! WTF ARE WE DOING NEED TO MAKE MORE READABLE
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
            if(_gridTypeIndicator[x][y] != EMPTY)
            {
                Node * currentNode = dynamic_cast<Node *>(board[x][y]);

                //right
                for(int i = x + 1; i<GAMEGRIDSIZE; i++)
                {
                    if(_gridTypeIndicator[i][y] != EMPTY)
                    {
                        currentNode->connectNodes(Direction::right, dynamic_cast<Node *>(board[i][y]));
                        break;
                    }
                }

                //left
                for(int i = x - 1; i>=0; i--)
                {
                    if(_gridTypeIndicator[i][y] != EMPTY)
                    {
                        currentNode->connectNodes(Direction::left, dynamic_cast<Node *>(board[i][y]));
                        break;
                    }
                }

                //bottom
                for(int i = y + 1; i<GAMEGRIDSIZE; i++)
                {
                    if(_gridTypeIndicator[x][i] != EMPTY)
                    {
                        currentNode->connectNodes(Direction::bottom, dynamic_cast<Node *>(board[x][i]));
                        break;
                    }
                }

                //top
                for(int i = y - 1; i>=0; i--)
                {
                    if(_gridTypeIndicator[x][i] != EMPTY)
                    {
                        currentNode->connectNodes(Direction::top, dynamic_cast<Node *>(board[x][i]));
                        break;
                    }
                }

            }
        }
    }
}

//update what should be highlighted
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

//clear what should be highlighted and update
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

//activate a specific direction
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

void GameLogic::enterMouseGridObjLine(GridObject *gridObj)
{
    clearHighlighted();
    _highLightedObjects.clear();

    Line * selectedLine = dynamic_cast<Line *>(gridObj);
    Node * firstNode = selectedLine->getFirstConnection();
    Node * secondNode = selectedLine->getSecondConnection();

    if(!(firstNode->isFull() || secondNode->isFull()) && !selectedLine->checkIsDouble())
    {
        selectedLine->setPotentialLine(true);
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
}

void GameLogic::updateCurrentDirection(GridObject *gridObj)
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
}

//implement logic. should have vector with all nodes?
bool GameLogic::isGameFinished()
{
    //for(int i=0; i<10; i++)//loop all nodes
    //{
    //    if(false)          //return if some is not full
    //        return false
    //}
    return true;           //return true if all is full
}

void GameLogic::endGame()
{
    qDebug() << "Game ended";
}
