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
        _logic.loadGameBoardFromFile(BOARDPATH);
    }catch(QString ERRORCODE)
    {QErrorMessage fileProblem(this); fileProblem.showMessage(ERRORCODE); fileProblem.exec();}
    _mainScene = new QGraphicsScene();
    _mainScene->setSceneRect(QRectF(0, 0, WINDOWSIZE, WINDOWSIZE));
    _mainView = new QGraphicsView(_mainScene);
    _mainView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
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

Hashlife::~Hashlife()
{

}
