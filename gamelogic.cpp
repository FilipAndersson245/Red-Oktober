#include    "gamelogic.h"
#define     GAMEGRIDSIZE 10
#define     MINDISTANCE 10
#define     DISPLACEMENTX 20
#define     DISPLACEMENTY 20
#define     NODEWIDTH 10
#define     NODEHEIGHT 10
#define     XCOMPENSATION 0
#define     YCOMPENSATION 0

GameLogic::GameLogic()
{

    _firstChoosenNode = nullptr;
    _secondChoosenNode = nullptr;
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
            }
        }
    }


}


void GameLogic::loadLevel(QByteArray infoFromFile)
{
    int infoNodeCounter = 0;
    QPoint passVectorElementIDAsPOS;
    GridObject* pushThisToVector;
    for (int i = 0; i < GAMEGRIDSIZE; ++i)
    {
        vector<GridObject*> temp;


        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            passVectorElementIDAsPOS.setX(j*DISPLACEMENTX);
            passVectorElementIDAsPOS.setY(i*DISPLACEMENTY);
            if((infoFromFile[infoNodeCounter]-'0') == 0)
            {
                pushThisToVector = nullptr;
            }
            else
            {
                pushThisToVector = new Node(passVectorElementIDAsPOS,1,(infoFromFile[infoNodeCounter]-'0'));
            }
            ++infoNodeCounter;
            temp.push_back(pushThisToVector);

        }
        _allGameObjects.push_back(temp);
    }
    qDebug() << "All nodes loaded correctly from file-data" ;
}

void GameLogic::addGraphicObjects(QGraphicsScene* aScene)
{


    for (int i = 0; i < _allGameObjects.size(); ++i)
    {

        for (int j = 0; j < _allGameObjects.size(); j++)
        {
            if (_allGameObjects[i][j] == nullptr)
                continue;
            aScene->addItem(_allGameObjects[i][j]);



        }
    }




}


void GameLogic::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "mouse pressed" << event->pos();

}



QPoint GameLogic::computeClick(QPoint position, QGraphicsScene* aScene, bool isRightClick)
{
    bool gridobjectClicked = false;
    for (int i = 0; i < _allGameObjects.size(); ++i)
    {

        for (int j = 0; j < _allGameObjects.size(); j++)
        {

            if (_allGameObjects[i][j] != nullptr)
            {
                // collision check //
                if (_allGameObjects[i][j]->isInside(position))
                {

                    // checks for line//
                    if (_allGameObjects[i][j]->getType() != 1)
                    {

                        continue;
                    }



                    if (_firstChoosenNode == nullptr)
                    {
                        gridobjectClicked = true;
                        qDebug() << "First clicked " << i << j <<endl << "@" <<_allGameObjects[i][j]->returnPosition() ;
                        _firstChoosenNode = _allGameObjects[i][j];
                        break;
                    }

                    else if (_secondChoosenNode == nullptr)
                    {
                        if (_allGameObjects[i][j] == _firstChoosenNode)
                        {
                            break;
                        }
                        gridobjectClicked = false;
                        qDebug() << "SEC clicked " << i << j <<endl << "@" <<_allGameObjects[i][j]->returnPosition() ;
                        _secondChoosenNode = _allGameObjects[i][j];


                        // try to make connection //
                        if(tryConnection(_firstChoosenNode, _secondChoosenNode, isRightClick))
                        {
                            addGraphicObjects(aScene);
                        }

                        qDebug() << "set connection";
                        break;
                    }
                }

            }
        }

    }


    if (!gridobjectClicked)
    {
        _firstChoosenNode = nullptr;
        _secondChoosenNode = nullptr;

    }

}
bool GameLogic::tryConnection(GridObject* firstNode, GridObject* secondNode, bool isRightClick)
{
    int firstConnectionToInputNode = 0;
    int dontDoConnection = 0;
    // check if any slots left //
    if (firstNode->returnNoOfConnections() == 0 || secondNode->returnNoOfConnections() == 0)
    {
        dontDoConnection = 1;
            // DEBUG DEBUG DEBUG //
        return false;
        }// check if connection to node exists //
    if (firstNode->hasConnectionWith(secondNode))
    {
        firstConnectionToInputNode = 1;

        // then check if exceeds limit //
        if(firstNode->hasExceededConnectionLimit(secondNode))
        {
            return false;
        }
    }

    QPoint firstNodeVectorPos(firstNode->returnPosition());
    firstNodeVectorPos.setX(firstNode->returnPosition().x()/DISPLACEMENTX);
    firstNodeVectorPos.setY(firstNode->returnPosition().y()/DISPLACEMENTY);

    QPoint secondNodeVectorPos(secondNode->returnPosition());
    secondNodeVectorPos.setX(secondNode->returnPosition().x()/DISPLACEMENTX);
    secondNodeVectorPos.setY(secondNode->returnPosition().y()/DISPLACEMENTY);

    // check same X or same Y //
    if (_firstChoosenNode->returnPosition().x() == _secondChoosenNode->returnPosition().x())
    {

        if (firstNodeVectorPos.y() < secondNodeVectorPos.y())
        {
            for (int i = firstNodeVectorPos.y()+1; i < secondNodeVectorPos.y();++i)
            {
                if(_allGameObjects[firstNodeVectorPos.x()][i] != nullptr)
                {
                    if (_allGameObjects[firstNodeVectorPos.x()][i]->getLineOrientation() == Orientation::horizontal)
                    {
                        return false;
                    }
                }

                else
                {

                    delete _allGameObjects[firstNodeVectorPos.x()][i];
                    _allGameObjects[firstNodeVectorPos.x()][i] = nullptr;

                    GridObject* pushLine = new Line(Orientation::vertical,QPoint(firstNodeVectorPos.x()*DISPLACEMENTX,i*DISPLACEMENTY),20);

                    pushLine->setPos(QPoint(firstNodeVectorPos.x()*DISPLACEMENTX,i*DISPLACEMENTY));
                    _allGameObjects[firstNodeVectorPos.x()][i] = pushLine;
                }
            }
            if(!dontDoConnection)
            {
                qDebug () << "connected nodes!";
                _firstChoosenNode->connectNode(_secondChoosenNode);
                _secondChoosenNode->connectNode(_firstChoosenNode);
            }
            return true;
        }
        else
        {    for (int i = secondNodeVectorPos.y()+1; i < firstNodeVectorPos.y();++i)
            {
                if(_allGameObjects[firstNodeVectorPos.x()][i] != nullptr)
                {
                    if (_allGameObjects[firstNodeVectorPos.x()][i]->getLineOrientation() == Orientation::horizontal)
                    {
                        return false;
                    }


                }

                else
                {
                    delete _allGameObjects[firstNodeVectorPos.x()][i];
                    _allGameObjects[firstNodeVectorPos.x()][i] = nullptr;

                    GridObject* pushLine = new Line(Orientation::vertical,QPoint(secondNodeVectorPos.x()*DISPLACEMENTX,i*DISPLACEMENTY),20);
                    _allGameObjects[firstNodeVectorPos.x()][i] = pushLine;
                }
            }
            if(!dontDoConnection)
            {
                qDebug () << "connected nodes!";
                _firstChoosenNode->connectNode(_secondChoosenNode);
                _secondChoosenNode->connectNode(_firstChoosenNode);
            }
            return true;

        }
    }
    else if (_firstChoosenNode->returnPosition().y() == _secondChoosenNode->returnPosition().y())
    {

        if (firstNodeVectorPos.x() < secondNodeVectorPos.x())
        {
            for (int i = firstNodeVectorPos.x()+1; i < secondNodeVectorPos.x();++i)
            {
                if(_allGameObjects[i][firstNodeVectorPos.y()] != nullptr)
                {
                    if (_allGameObjects[i][firstNodeVectorPos.y()]->getLineOrientation() == Orientation::vertical)
                    {
                        return false;
                    }


                }

                else
                {
                    delete _allGameObjects[i][firstNodeVectorPos.y()];
                    _allGameObjects[i][firstNodeVectorPos.y()] = nullptr;

                    GridObject* pushLine = new Line(Orientation::horizontal,QPoint(i*DISPLACEMENTX,firstNodeVectorPos.y()*DISPLACEMENTY),20);
                    _allGameObjects[i][firstNodeVectorPos.y()] = pushLine;
                }
            }
        }
        else
        {    for (int i = secondNodeVectorPos.x()+1; i < firstNodeVectorPos.x();++i)
            {

                if(_allGameObjects[i][firstNodeVectorPos.y()] != nullptr)
                {
                    if (_allGameObjects[i][firstNodeVectorPos.y()]->getLineOrientation() == Orientation::vertical)
                    {

                        return false;
                    }


                }

                delete _allGameObjects[i][firstNodeVectorPos.y()];
                _allGameObjects[i][firstNodeVectorPos.y()] = nullptr;

                GridObject* pushLine = new Line(Orientation::horizontal,QPoint(i*DISPLACEMENTX,firstNodeVectorPos.y()*DISPLACEMENTY),20);
                _allGameObjects[i][firstNodeVectorPos.y()] = pushLine;
            }

        }
        if(!dontDoConnection)
        {
            qDebug () << "connected nodes!";
            _firstChoosenNode->connectNode(_secondChoosenNode);
            _secondChoosenNode->connectNode(_firstChoosenNode);
        }
        return true;
    }
    return false;
}




