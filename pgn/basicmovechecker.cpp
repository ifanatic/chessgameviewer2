#include "basicmovechecker.h"

BasicMoveChecker::BasicMoveChecker()
{
}

bool BasicMoveChecker::canMoveTo(int row, int col, PieceColor color,
                                 int rowDest, int colDest,
                                 const ChessBoard& chessBoard)
{
    if((rowDest < 0) || (rowDest > 7) || (colDest < 0) || (colDest > 7))
    {
        return false;
    }

    if(chessBoard.isEmpty(rowDest, colDest))
    {
        return true;
    }

    if(chessBoard.getColor(rowDest, colDest) == color)
    {
        return false;
    }

    return true;
}
