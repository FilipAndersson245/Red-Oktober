#ifndef HASHLIFE_H
#define HASHLIFE_H
#include "gamelogic.h"
#include <QMainWindow>

namespace Ui {
class Hashlife;
}

class Hashlife : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hashlife(QWidget *parent = 0);
    ~Hashlife();

private:
    Ui::Hashlife *ui;
    GameLogic _logic;
};

#endif // HASHLIFE_H
//
