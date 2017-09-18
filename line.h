#ifndef LINE_H
#define LINE_H
#include "gridobject.h"

class Line : public GridObject
{
public:
    Line(int x, int y);
    ClassTypes getClass();

private:
    bool _isVertical = 0;

};

#endif // LINE_H
//
