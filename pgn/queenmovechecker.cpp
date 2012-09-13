#include "queenmovechecker.h"

void QueenMoveChecker::initDirections()
{
    _directions = new int*[8];
    for(int i = 0; i < 8; ++i)
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

    _directions[4][0] = -1;
    _directions[4][1] = -1;

    _directions[5][0] = -1;
    _directions[5][1] =  1;

    _directions[6][0] =  1;
    _directions[6][1] =  1;

    _directions[7][0] =  1;
    _directions[7][1] = -1;

    _directionsCount = 8;
}

QueenMoveChecker::QueenMoveChecker()
{
    initDirections();
}
