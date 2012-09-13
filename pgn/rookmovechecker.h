#ifndef ROOKMOVECHECKER_H
#define ROOKMOVECHECKER_H

#include "directionmovechecker.h"

class RookMoveChecker : public DirectionMoveChecker
{
private:
    virtual void initDirections();

public:
    RookMoveChecker();
};

#endif // ROOKMOVECHECKER_H
