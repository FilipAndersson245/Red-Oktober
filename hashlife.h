#ifndef HASHLIFE_H
#define HASHLIFE_H
#include "gamelogic.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <iostream>
#include <QGraphicsEllipseItem>
namespace Ui {
class Hashlife;
}

class Hashlife : public QWidget
{
    Q_OBJECT

public:
    explicit Hashlife(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);
    void addGraphicObjects();
    ~Hashlife();
private:
    void resizeEvent(QResizeEvent *event) override;
    void autoScaleView();

    Ui::Hashlife *ui;
    QGraphicsScene* _mainScene;
    QGraphicsView* _mainView;
    GameLogic _logic;
    QPoint _clickedPos;

};

#endif // HASHLIFE_H
