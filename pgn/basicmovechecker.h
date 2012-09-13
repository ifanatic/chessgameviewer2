#ifndef BASICMOVECHECKER_H
#define BASICMOVECHECKER_H

#include "chessboard.h"

class BasicMoveChecker
{
public:
    BasicMoveChecker();
    virtual ~BasicMoveChecker() { }

    virtual bool canMoveTo(int row, int col, PieceColor color,
                           int rowDest, int colDest,
                           const ChessBoard& chessBoard);
};

#endif // BASICMOVECHECKER_H
