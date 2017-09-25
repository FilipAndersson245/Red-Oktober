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
#include <QPushButton>
#include <QButtonGroup>
#include <QApplication>
#include <QGraphicsItem>
#include <QComboBox>
#include <QGraphicsProxyWidget>
#include <QShowEvent>
#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QDialog>

#define BOARDPATH "./level1.hashiboard"
#define GAMEGRIDSIZE 10
#define WINDOWSIZE 200

namespace Ui {
class Hashlife;
}

class Hashlife : public QMainWindow
{

    Q_OBJECT

public:

    explicit Hashlife(QWidget *parent = 0);

    void addMenuGraphics();

    void setupGameGraphics();

    ~Hashlife();

    int returnRandom();
    void choosenMap(int userDifficultyChoice, int userBoardSize);
public slots:

    void setupGame();

    void newGame();

    void help();

    void exit();

    void returnToMenu();

private slots:

    void on_actionEnd_Game_triggered();

    void on_actionHelp_triggered();

private:

    void resizeEvent(QResizeEvent *event) override;

    void showEvent(QShowEvent *event) override;

    void autoScaleView();

    Ui::Hashlife *ui;

    QGraphicsScene* _mainScene;

    GameLogic _logic;

    QPushButton *_btnNewGame;

    QGraphicsProxyWidget *_proxyNewGame;

    QPushButton *_btnHelp;

    QGraphicsProxyWidget *_proxyHelp;

    QPushButton *_btnExit;

    QGraphicsProxyWidget *_proxyExit;

    QPushButton *_btnReturn;

    QGraphicsProxyWidget *_proxyReturn;

    QPushButton *_btnGrid10;

    QGraphicsProxyWidget *_proxyGrid10;

    QPushButton *_btnGrid15;

    QGraphicsProxyWidget *_proxyGrid15;

    QPushButton *_btnGrid20;

    QGraphicsProxyWidget *_proxyGrid20;

    QPushButton *_btnEasy;

    QGraphicsProxyWidget *_proxyEasy;

    QPushButton *_btnMedium;

    QGraphicsProxyWidget *_proxyMedium;

    QPushButton *_btnHard;

    QGraphicsProxyWidget *_proxyHard;

    QPushButton *_btnStart;

    QGraphicsProxyWidget *_proxyStart;

    QComboBox *_boardSelector = 0;

    QGraphicsProxyWidget *_proxyBoardSelector;

    QButtonGroup *_grpGridSize;

    QButtonGroup *_grpDifficulty;

};
