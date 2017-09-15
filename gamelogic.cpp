#include "gamelogic.h"
#define GAMEGRIDSIZE 10
#define MINDISTANCE 20
GameLogic::GameLogic()
{
    QPoint positionOfNode;
    for (int i = 0; i < GAMEGRIDSIZE; i++)
    {
        vector<GridObject*> temp;
        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            positionOfNode.setX(i*50);
            positionOfNode.setY(j*50);
            GridObject* hej = new Node(positionOfNode);
            temp.push_back(hej);
        }
        _allGameObjects.push_back(temp);

    }

}

QPoint GameLogic::returnPosition(int index)
{
    return QPoint(index*20,index*10);
}

void GameLogic::paintAll(QPainter* painter)
{
    // painting is now done in seperate class //

//    QPoint vectorpos;
//    int k = 0;
//    for (int i = 0; i < _allGameObjects.size(); ++i)
//    {
////        vectorpos.setX(i);
////        vectorpos.setY(0);

//      //  _allGameObjects[i][0]->paintMember(painter,vectorpos);
//        for (int j = 0; j < GAMEGRIDSIZE; j++)
//        {

//           _allGameObjects[j][i]->paintMember(painter);
//           ++k;

//        }
 }


bool GameLogic::setNodeConnection(QPoint firstNodeVectorPos, QPoint secondVectorPos)
{
    // acessing first node from vector //
    //_allGameObjects[firstNodeVectorPos.x()][firstNodeVectorPos.y()]->getSlotMap();
    // accessing second node from vector //
   // _allGameObjects[secondVectorPos.x()][secondVectorPos.y()]->getSlotMap();


}

QPoint GameLogic::isCloseToNode(QPoint position)
{

    for (int i = 0; i < _allGameObjects.size(); ++i)
    {

        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            QPoint distance = _allGameObjects[j][i]->returnPosition() - position;
            if (distance.manhattanLength() < MINDISTANCE)
            {
                return _allGameObjects[j][i]->returnPosition();
            }


        }
    }
}

vector<vector<GridObject *> > GameLogic::getGameVector()
{
    return _allGameObjects;
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
           while (!boardFile.atEnd()) {
                  nodePositionData.append(boardFile.readLine());
           }
       if (boardFile.atEnd())
       {

           for (int i = 0; i < nodePositionData.length(); ++i)
               if (nodePositionData[i] != '\n')
               {

                   nodePositionDataFormatted.append(nodePositionData[i]);
               }

           if(nodePositionDataFormatted.length() != (GAMEGRIDSIZE*GAMEGRIDSIZE))
           {
               throw (QString("Board file data is wrong/corrupt please fix"));
           }

           else
               {
               setUpNodesWithFileInfo(nodePositionDataFormatted);

           }


       }
}

void GameLogic::setUpNodesWithFileInfo(QByteArray infoFromFile)
{
    int infoNodeCounter = 0;
    for (int i = 0; i < _allGameObjects.size(); ++i)
    {

        for (int j = 0; j < _allGameObjects.size(); j++)
        {
              qDebug() << infoFromFile[infoNodeCounter]-'0';
            _allGameObjects[j][i]->setMaximumNodeConnections(infoFromFile[infoNodeCounter]-'0');
            ++infoNodeCounter;
        }
}
    qDebug() << "All nodes loaded correctly from file-data";
}
