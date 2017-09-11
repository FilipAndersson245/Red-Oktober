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
    // do collision check here //
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
