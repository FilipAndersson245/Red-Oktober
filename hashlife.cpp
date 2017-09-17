#include "hashlife.h"
#include "ui_hashlife.h"
#define BOARDPATH "c:/level1.hashiboard"
Hashlife::Hashlife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hashlife)
{
    // loading game info from level file and setting up board //
    try{
         _logic.loadGameBoardFromFile(BOARDPATH);
        }catch(QString ERRORCODE)
        {QErrorMessage fileProblem(this); fileProblem.showMessage(ERRORCODE); fileProblem.exec();}


    _mainScene = new QGraphicsScene();
    _mainScene->setSceneRect(QRectF(0, 0, WINDOWSIZE, WINDOWSIZE));
    _mainView = new QGraphicsView(_mainScene);


    QVBoxLayout* vlayout = new QVBoxLayout(this);

    vlayout->addWidget(_mainView);
    autoScaleView();
    addGraphics();
    this->show();
}

void Hashlife::addGraphics()
{

          // retrieve vector from logic class and add to scene //
       vector<vector<GridObject*> > returnedVector;
       returnedVector = _logic.getGameVector();

       for (int i = 0; i < returnedVector.size(); ++i)
       {

           for (int j = 0; j < returnedVector.size(); j++)
           {

               _mainScene->addItem(returnedVector[i][j]);

           }
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
