#include "gamelogic.h"
#define GAMEGRIDSIZE 10
#define DISPLACEMENTX 20
#define  DISPLACEMENTY 20
GameLogic::GameLogic()
{

}

void GameLogic::loadGameBoardFromFile(QString userLevelChoice)
{
    QByteArray nodePositionData;
    QByteArray nodePositionDataFormatted;
    QFile boardFile(userLevelChoice);
    if (!boardFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw (QString("board info file cant be opened! I looked here: "+userLevelChoice));
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
            currentNumber = (infoFromFile[(j * 10) + i]-'0');
            passVectorElementIDAsPOS.setX(i*DISPLACEMENTX);
            passVectorElementIDAsPOS.setY(j*DISPLACEMENTY);
            if(currentNumber == 0)
            {
                pushThisToVector = new Empty(i, j, passVectorElementIDAsPOS, WINDOWSIZE/GAMEGRIDSIZE);
                connect(pushThisToVector, SIGNAL(addLine(Empty*)), this, SLOT(emptyToLine(Empty*)));
            }
            else
            {
                pushThisToVector = new Node(i, j, (currentNumber), passVectorElementIDAsPOS, WINDOWSIZE/GAMEGRIDSIZE);
                connect(pushThisToVector, SIGNAL(mouseEnter(Node*)), this, SLOT(viewPotential(Node*)));
            }
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

void GameLogic::emptyToLine(Empty *empty)
{
    qDebug() << "tried to make line";
    int x = empty->getXPos();
    int y = empty->getYPos();
    QPoint point(x*(WINDOWSIZE/GAMEGRIDSIZE), y*(WINDOWSIZE/GAMEGRIDSIZE));
    Orientation ori = Orientation::vertical;
    GridObject* line = new Line(x, y, ori, point, WINDOWSIZE/GAMEGRIDSIZE);
    connect(line, SIGNAL(addEmpty(Line*)), this, SLOT(linetoEmpty(Line*)));
    bool ok = empty ==  _allGameObjects[x][y];
    qDebug() << " ok is " << ok;
    _allGameObjects[x][y] = line;
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
    connect(empty, SIGNAL(addLine(Empty*)), this, SLOT(emptyToLine(Empty*)));
    _allGameObjects[x][y] = empty;
    _gameScene->removeItem(line);
    _gameScene->addItem(_allGameObjects[x][y]);
}

void GameLogic::viewPotential(Node *node)
{
    for(auto &objectVector : node->getAllPotentialLines(&_allGameObjects))
    {
        int a = 5;
        for(GridObject * object : objectVector.second)
        {
            if(object == nullptr)
            {
                break;
            }
            Empty * gridTile = dynamic_cast<Empty *>(object);
            gridTile->setBrush(QBrush(Qt::yellow));
        }
    }
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
