#pragma once

#include "gamelogic.h"
#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <iostream>
#include <QDialog>
#include <QErrorMessage>

#define GAMEGRIDSIZE 10
#define WINDOWSIZE 200

namespace Ui {
class Hashlife;
}

class Hashlife : public QWidget
{
    Q_OBJECT

public:

    explicit Hashlife(QWidget *parent = 0);

    void addGraphics();
    ~Hashlife();

private:

    void resizeEvent(QResizeEvent *event) override;

    void autoScaleView();

    Ui::Hashlife *ui;

    QGraphicsScene* _mainScene;

    QGraphicsView* _mainView;

    GameLogic _logic;

    //test, behöver skicka med qwidget/qscene som argument till gamelogic på något sätt.

    vector<vector<GridObject*> > _allGameObjects;
};
