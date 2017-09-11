#include "gamelogic.h"
#define GAMEGRIDSIZE 10

GameLogic::GameLogic()
{
    for (int i = 0; i < GAMEGRIDSIZE; i++)
    {
        vector<GridObject*> temp;
        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            GridObject* hej = new Node();
            temp.push_back(hej);
        }
        _allGameObjects.push_back(temp);

    }
}
