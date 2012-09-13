#ifndef QUEENMOVECHECKER_H
#define QUEENMOVECHECKER_H

#include "directionmovechecker.h"

class QueenMoveChecker : public DirectionMoveChecker
{
private:
    virtual void initDirections();

public:
    QueenMoveChecker();
};

#endif // QUEENMOVECHECKER_H
