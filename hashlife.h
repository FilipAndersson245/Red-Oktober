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
#include <QErrorMessage>
#include <QFont>
#include <QGraphicsTextItem>
#include "gamemenu.h"
#include <QFileDialog>
namespace Ui {
class Hashlife;
}

class Hashlife : public QWidget
{
    Q_OBJECT

public:
    explicit Hashlife(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* event);


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
