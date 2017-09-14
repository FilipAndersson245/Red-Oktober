#include "hashlife.h"
#include "ui_hashlife.h"
#define NODEWIDTH 40
#define NODEHEIGHT 40
#define XCOMPENSATION +11
#define YCOMPENSATION +6
// get this to work with relative path //
#define BOARDPATH "c:/hashi/gameBoardToLoad.txt"
Hashlife::Hashlife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hashlife)
{
    try{
     _logic.loadGameBoardFromFile(BOARDPATH);
    }catch(QString ERRORCODE)
            // not showing :( //
    {QErrorMessage fileProblem(this); fileProblem.showMessage(ERRORCODE);}


    _mainScene = new QGraphicsScene();
   // _mainScene->setSceneRect(QRectF(0, 0, 200, 200));
    _mainView = new QGraphicsView(_mainScene);
  //  QGraphicsRectItem *rect = _mainScene->addRect(QRectF(_mainScene->sceneRect()));
    addGraphicObjects();


    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addWidget(_mainView);
    autoScaleView();
    this->show();
}

void Hashlife::resizeEvent(QResizeEvent *event)
{
    autoScaleView();
}

void Hashlife::autoScaleView()
{
    _mainView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
}

void Hashlife::mousePressEvent(QMouseEvent *event)
{
    _clickedPos = event->pos();
    if (!_logic.isCloseToNode(event->pos()).isNull())
    {
        //_logic.setNodeConnection(QPoint firstNodeVectorPos, QPoint secondVectorPos);
    }
    // do collision check here //
}

void Hashlife::mouseMoveEvent(QMouseEvent *event)
{
if (!_logic.isCloseToNode(event->pos()).isNull())
{

        qDebug() << _logic.isCloseToNode(event->pos());

}
}

void Hashlife::paintEvent(QPaintEvent *event)
{

        QPainter Painter(this);
        _logic.paintAll(&Painter);
}

void Hashlife::addGraphicObjects()
{
    // retrieve vector from logic class //
    vector<vector<GridObject*> > returnedVector;
    returnedVector = _logic.getGameVector();

        // create node graphic objects //
    QSize sizeOfNodeGraphic(NODEWIDTH,NODEHEIGHT);

    for (int i = 0; i < returnedVector.size(); ++i)
    {

        for (int j = 0; j < returnedVector.size(); j++)
        {

             QRectF boundingRectForGraphicItem (returnedVector[i][j]->returnPosition(), sizeOfNodeGraphic);
             QString noOfConnections = QString::number(returnedVector[i][j]->returnNoOfConnections());
             // set graphic specifics //
             QGraphicsEllipseItem nodeGraphicObject(boundingRectForGraphicItem);

             QPen penForEllipse(Qt::blue);
             QBrush brushForEllipse(Qt::blue,Qt::SolidPattern);





             if (noOfConnections != "0")


             {

             _mainScene->addEllipse(boundingRectForGraphicItem);
              QGraphicsTextItem* connectionDescription = _mainScene->addText(noOfConnections);
              connectionDescription->setPos(boundingRectForGraphicItem.x()+XCOMPENSATION,boundingRectForGraphicItem.y()+YCOMPENSATION);

             }
             }
    }




}

Hashlife::~Hashlife()
{
    delete ui;
}
