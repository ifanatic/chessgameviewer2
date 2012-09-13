#include "rookmovechecker.h"

void RookMoveChecker::initDirections()
{
    _directions = new int*[4];
    for(int i = 0; i < 4; ++i)
    {
        _directions[i] = new int[2];
    }

    _directions[0][0] = -1;
    _directions[0][1] =  0;

    _directions[1][0] =  0;
    _directions[1][1] =  1;

    _directions[2][0] =  1;
    _directions[2][1] =  0;

    _directions[3][0] =  0;
    _directions[3][1] = -1;

    _directionsCount = 4;
}

RookMoveChecker::RookMoveChecker()
{
    initDirections();
}
