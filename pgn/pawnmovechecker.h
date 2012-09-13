#ifndef PAWNMOVECHECKER_H
#define PAWNMOVECHECKER_H

#include "basicmovechecker.h"

class PawnMoveChecker : public BasicMoveChecker
{
public:
    PawnMoveChecker();

    virtual bool canMoveTo(int row, int col, PieceColor color,
                           int rowDest, int colDest,
                           const ChessBoard& chessBoard);
};

#endif // PAWNMOVECHECKER_H
