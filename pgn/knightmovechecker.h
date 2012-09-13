#ifndef KNIGHTMOVECHECKER_H
#define KNIGHTMOVECHECKER_H

#include "basicmovechecker.h"
#include "chessboard.h"

class KnightMoveChecker : public BasicMoveChecker
{
private:
    int _directions[8][2];

public:
    KnightMoveChecker();

    virtual bool canMoveTo(int row, int col, PieceColor color,
                           int rowDest, int colDest,
                           const ChessBoard& chessBoard);
};

#endif // KNIGHTMOVECHECKER_H
