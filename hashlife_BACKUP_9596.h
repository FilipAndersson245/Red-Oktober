#ifndef HASHLIFE_H
#define HASHLIFE_H
#include "gamelogic.h"
<<<<<<< HEAD
#include <QMainWindow>
#include <QMouseEvent>
=======
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <iostream>

>>>>>>> origin/Scene
namespace Ui {
class Hashlife;
}

class Hashlife : public QWidget
{
    Q_OBJECT

public:
    explicit Hashlife(QWidget *parent = 0);
<<<<<<< HEAD
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
=======

>>>>>>> origin/Scene
    ~Hashlife();

    void paintEvent(QPaintEvent *event);
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
