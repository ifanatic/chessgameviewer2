#ifndef BISHOPMOVECHECKER_H
#define BISHOPMOVECHECKER_H

#include "directionmovechecker.h"

class BishopMoveChecker : public DirectionMoveChecker
{
private:
    virtual void initDirections();

public:
    BishopMoveChecker();
};

#endif // BISHOPMOVECHECKER_H
