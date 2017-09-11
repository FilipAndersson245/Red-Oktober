#include "gamelogic.h"
#define GAMEGRIDSIZE 10

GameLogic::GameLogic()
{
    for (int i = 0; i < GAMEGRIDSIZE; i++)
    {
        vector<GridObject*> temp;
        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            GridObject* hej = new Node(returnPosition(j));
            temp.push_back(hej);
        }
        _allGameObjects.push_back(temp);
    qDebug () << "hrj";
    }

}

QPoint GameLogic::returnPosition(int index)
{
    return QPoint(index*20,index*10);
}

void GameLogic::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (int i = 0; i < _allGameObjects.size(); ++i)
    {
        _allGameObjects.at(i)->paintMember(%painter);
    }
}
