#include "hashlife.h"
#include "ui_hashlife.h"

Hashlife::Hashlife(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hashlife)
{
    ui->setupUi(this);
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

Hashlife::~Hashlife()
{
    delete ui;
}
