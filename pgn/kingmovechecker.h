#ifndef KINGMOVECHECKER_H
#define KINGMOVECHECKER_H

#include "basicmovechecker.h"

class KingMoveChecker : public BasicMoveChecker
{
private:
    int _directions[8][2];

public:
    KingMoveChecker();

    virtual bool canMoveTo(int row, int col, PieceColor color,
                               int rowDest, int colDest,
                               const ChessBoard& chessBoard);
};

#endif // KINGMOVECHECKER_H
