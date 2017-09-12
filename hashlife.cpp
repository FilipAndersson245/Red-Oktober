#include "hashlife.h"
#include "ui_hashlife.h"

Hashlife::Hashlife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hashlife)
{
    _mainScene = new QGraphicsScene();
    _mainScene->setSceneRect(QRectF(0, 0, WINDOWSIZE, WINDOWSIZE));
    _mainView = new QGraphicsView(_mainScene);
    //QGraphicsRectItem *rect = _mainScene->addRect(QRectF(_mainScene->sceneRect()));

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
            GridObject* hej = new Line(0);

            temp.push_back(hej);

            temp.at(j)->setPos(xposition, yposition);

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
