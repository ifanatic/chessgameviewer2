#include "kingmovechecker.h"

KingMoveChecker::KingMoveChecker()
{
    _directions[0][0] = -1;
    _directions[0][1] =  0;

    _directions[1][0] = -1;
    _directions[1][1] =  1;

    _directions[2][0] =  0;
    _directions[2][1] =  1;

    _directions[3][0] =  1;
    _directions[3][1] =  1;

    _directions[4][0] =  1;
    _directions[4][1] =  0;

    _directions[5][0] =  1;
    _directions[5][1] = -1;

    _directions[6][0] =  0;
    _directions[6][1] = -1;

    _directions[7][0] = -1;
    _directions[7][1] = -1;

}

bool KingMoveChecker::canMoveTo(int row, int col, PieceColor color,
                               int rowDest, int colDest,
                               const ChessBoard& chessBoard)
{
    for(int i = 0; i < 8; ++i)
    {
        if(!BasicMoveChecker::canMoveTo(row + _directions[i][1], col + _directions[i][0],
                                       color, rowDest, colDest, chessBoard))
        {
            continue;
        }

        if(((row + _directions[i][1]) == rowDest) && ((col + _directions[i][0]) == colDest))
        {
            return true;
        }
    }


    return false;
}
