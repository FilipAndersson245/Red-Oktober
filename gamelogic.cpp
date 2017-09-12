#include "gamelogic.h"
#define GAMEGRIDSIZE 10

GameLogic::GameLogic()
{
    //_gameScene = scene;
    for (int i = 0; i < GAMEGRIDSIZE; i++)
    {
        vector<GridObject*> temp;
        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            GridObject* hej = new Node(2);
            temp.push_back(hej);
        }
        _allGameObjects.push_back(temp);

    }
}
