#include "hashlife.h"
#include "ui_hashlife.h"
#define STARTPATH ":/levels"

#include <QDir>
// get this to work with relative path //
#define BOARDPATH ":/levels/EASY_10x10_level1.hashiboard"
Hashlife::Hashlife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hashlife)
{

QString choosenBoardPath = "";
    // loading game info from level file and setting up board //
   // QFileDialog userInput(this,"Choose level file",STARTPATH,"*.hashiboard");
    //choosenBoardPath = userInput.getOpenFileName();
    try{
         _logic.loadGameBoardFromFile(BOARDPATH);
        }catch(QString ERRORCODE)
        {QErrorMessage fileProblem(this); fileProblem.showMessage(ERRORCODE); fileProblem.exec();}

       _mainScene = new QGraphicsScene();
       _mainScene->setSceneRect(QRectF(0, 0, 200, 200));
       _mainView = new QGraphicsView(_mainScene);


       QVBoxLayout* vlayout = new QVBoxLayout(this);

       vlayout->addWidget(_mainView);
       autoScaleView();
       _logic.addGraphicObjects(_mainScene);
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
    bool isRightClick = false;
    QPointF returnedPoint = _mainView->mapToScene(event->pos());

    if (event->button() == Qt::RightButton)
    {
       qDebug() << event->type();
        isRightClick = true;
    }
    QPoint reMappedPoint;
    reMappedPoint.setX(returnedPoint.x());
    reMappedPoint.setY(returnedPoint.y());

    // run main event //
    qDebug() << isRightClick;
    _logic.computeClick(reMappedPoint, _mainScene,isRightClick);

}





Hashlife::~Hashlife()
{
    delete ui;
}
