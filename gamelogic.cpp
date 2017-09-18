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
            passVectorElementIDAsPOS.setX(i*DISPLACEMENTX);
            passVectorElementIDAsPOS.setY(j*DISPLACEMENTY);
            if((infoFromFile[infoNodeCounter]-'0') == 0)
            {
                pushThisToVector = new Empty(passVectorElementIDAsPOS, WINDOWSIZE/GAMEGRIDSIZE);
            }
            else
            {
                pushThisToVector = new Node((infoFromFile[infoNodeCounter]-'0'), passVectorElementIDAsPOS, WINDOWSIZE/GAMEGRIDSIZE);
            }
            ++infoNodeCounter;
            temp.push_back(pushThisToVector);

        }
        _allGameObjects.push_back(temp);
    }
    qDebug() << "All nodes loaded correctly from file-data";
}
vector<vector<GridObject*> > GameLogic::getGameVector(void)
{
    return _allGameObjects;
}

void GameLogic::addGameGraphics(QGraphicsScene* aScene)
{


 for (int i = 0; i < _allGameObjects.size(); ++i)
 {

     for (int j = 0; j < _allGameObjects.size(); j++)
     {

         aScene->addItem(_allGameObjects[i][j]);

     }
 }

}
