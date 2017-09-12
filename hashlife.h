#ifndef HASHLIFE_H
#define HASHLIFE_H
#include "gamelogic.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <iostream>

namespace Ui {
class Hashlife;
}

class Hashlife : public QWidget
{
    Q_OBJECT

public:
    explicit Hashlife(QWidget *parent = 0);

    ~Hashlife();

private:
    void resizeEvent(QResizeEvent *event) override;
    void autoScaleView();

    Ui::Hashlife *ui;
    QGraphicsScene* _mainScene;
    QGraphicsView* _mainView;
    GameLogic _logic;
};

#endif // HASHLIFE_H
