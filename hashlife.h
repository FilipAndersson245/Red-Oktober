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
#include <time.h>

#define ROOTDIR ":/levels/"
#define GAMEGRIDSIZE 10
#define WINDOWSIZE 200
#define NOOFLEVELS 4

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

    // calling map load with user specified map //
    void choosenMap(int userDifficultyChoice, int userBoardSize);
    // returns random int for board path loading //
    int returnRandom();
private:

    void resizeEvent(QResizeEvent *event) override;

    void autoScaleView();

    Ui::Hashlife *ui;

    QGraphicsScene* _mainScene;

    QGraphicsView* _mainView;

    GameLogic _logic;

};
