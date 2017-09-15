#include "hashlife.h"
#include "ui_hashlife.h"

Hashlife::Hashlife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hashlife)
{
    _mainScene = new QGraphicsScene();
    _mainScene->setSceneRect(QRectF(0, 0, WINDOWSIZE, WINDOWSIZE));
    _mainView = new QGraphicsView(_mainScene);


    QVBoxLayout* vlayout = new QVBoxLayout(this);

    vlayout->addWidget(_mainView);

    addNodeToGameObjects();

    autoScaleView();
    this->show();
}

void Hashlife::addNodeToGameObjects()
{

    int yposition = 0;
    for (int i = 0; i < GAMEGRIDSIZE; i++)
    {
        int xposition = 0;
        vector<GridObject*> temp;
        for (int j = 0; j < GAMEGRIDSIZE; j++)
        {
            QPoint posPoint(xposition, yposition);
            Orientation orient = Orientation::horizontal;

            if ((j == 4 && i == 5) || (j == 6 && i == 5))
            {
                GridObject* hej = new Node(2, posPoint, WINDOWSIZE/GAMEGRIDSIZE);
                temp.push_back(hej);
            }
            else if (j == 5 && i == 5)
            {
                GridObject* hej = new Line(orient, posPoint, WINDOWSIZE/GAMEGRIDSIZE);
                temp.push_back(hej);
            }
            else
            {
                GridObject* hej = new Empty(posPoint, WINDOWSIZE/GAMEGRIDSIZE);
                temp.push_back(hej);
            }

            _mainScene->addItem(temp.at(j));
            xposition+= WINDOWSIZE/GAMEGRIDSIZE;
        }
        _allGameObjects.push_back(temp);
        yposition += WINDOWSIZE/GAMEGRIDSIZE;
    }
}

void Hashlife::resizeEvent(QResizeEvent *event)
{
    autoScaleView();
}

void Hashlife::autoScaleView()
{
    _mainView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
}

Hashlife::~Hashlife()
{

}
