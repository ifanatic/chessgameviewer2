#ifndef DIRECTIONMOVECHECKER_H
#define DIRECTIONMOVECHECKER_H

#include "basicmovechecker.h"
#include "chessboard.h"

class DirectionMoveChecker : public BasicMoveChecker
{
protected:
    int** _directions;
    int _directionsCount;

    virtual void initDirections() = 0;

public:
    DirectionMoveChecker();
    virtual ~DirectionMoveChecker();

    virtual bool canMoveTo(int row, int col, PieceColor color,
                           int rowDest, int colDest,
                           const ChessBoard& chessBoard);
};

#endif // DIRECTIONMOVECHECKER_H
