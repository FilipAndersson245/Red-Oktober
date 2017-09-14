#ifndef HASHLIFE_H
#define HASHLIFE_H
#include "gamelogic.h"
#include <QMainWindow>
#include <QMouseEvent>
namespace Ui {
class Hashlife;
}

class Hashlife : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hashlife(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    ~Hashlife();

    void paintEvent(QPaintEvent *event);
private:
    Ui::Hashlife *ui;
    GameLogic _logic;
    QPoint _clickedPos;

};

#endif // HASHLIFE_H
