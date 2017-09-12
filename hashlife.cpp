#include "hashlife.h"
#include "ui_hashlife.h"

Hashlife::Hashlife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hashlife)
{
    _mainScene = new QGraphicsScene();
    _mainScene->setSceneRect(QRectF(0, 0, 200, 200));
    _mainView = new QGraphicsView(_mainScene);
    QGraphicsRectItem *rect = _mainScene->addRect(QRectF(_mainScene->sceneRect()));

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

Hashlife::~Hashlife()
{
    delete ui;
}
