#include "hashlife.h"
#include "ui_hashlife.h"
#define BOARDPATH "../level1.hashiboard"
Hashlife::Hashlife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hashlife)
{
    // loading game info from level file and setting up board //
    try
    {
        int difficultyChoosen = 2;
        int boardSizeChoosen = 1;
        choosenMap(difficultyChoosen,boardSizeChoosen);

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
    _logic.addGameGraphics(_mainScene);
}

void Hashlife::resizeEvent(QResizeEvent *event)
{
    autoScaleView();
}

void Hashlife::autoScaleView()
{
    _mainView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
}

void Hashlife::choosenMap(int userDifficultyChoice, int userBoardSize)
{
    QString loadThisTypeOfBoard = ROOTDIR;
    switch (userDifficultyChoice)
    {

    case 1:
    {
        loadThisTypeOfBoard.append("EASY");
    }
        break;
    case 2:
    {
        loadThisTypeOfBoard.append("MEDIUM");
    }
        break;
    case 3:
    {
        loadThisTypeOfBoard.append("HARD");
    }
        break;
        // Never end up here //
    default:
    {
        throw(QString ("something went wrong while computing user lever choice"));
    }
    }
    switch (userBoardSize)
    {

    case 1:
    {
        loadThisTypeOfBoard.append("_10x10");
    }
        break;
    case 2:
    {
        loadThisTypeOfBoard.append("_15x15");
    }
        break;
    case 3:
    {
        loadThisTypeOfBoard.append("_20x20");
    }
        break;
        // Never end up here //
    default:
    {
        throw(QString ("something went wrong while computing user lever choice"));
    }
    }
    if (!loadThisTypeOfBoard.isEmpty())
    {
        // dot is for identification of new info //
        loadThisTypeOfBoard.append("_level" + QString::number(returnRandom()) +".hashiboard");

        qDebug() << "User level choice:" << loadThisTypeOfBoard;

        _logic.loadGameBoardFromFile(loadThisTypeOfBoard);
    }




}


int Hashlife::returnRandom(void)
{
    srand((int)time(NULL));
    int randNum = (rand() % NOOFLEVELS) + 1;
    return randNum;
}
Hashlife::~Hashlife()
{

}
