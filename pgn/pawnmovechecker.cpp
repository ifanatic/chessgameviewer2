#include "pawnmovechecker.h"

#include <iostream>

PawnMoveChecker::PawnMoveChecker()
{
}

bool PawnMoveChecker::canMoveTo(int row, int col, PieceColor color,
                                int rowDest, int colDest,
                                const ChessBoard& chessBoard)
{
//    std::cout << "PawnMoveChecker" << std::endl;
//    std::cout << "rowDest: " << rowDest << ", colDest: " << colDest << std::endl;
    if(!BasicMoveChecker::canMoveTo(row, col, color, rowDest, colDest, chessBoard))
    {
//        std::cout << "<!" << std::endl;
        return false;
    }

    int direction = (color == White) ? 1 : -1;

    for(int i = -1; i <= 1; ++i)
    {
        if(i == 0)
        {
            if(!chessBoard.isEmpty(row + direction, col))
            {
                continue;
            }
        }
        else
        {
            if((chessBoard.getColor(row + direction, col + i) == color) ||
                    chessBoard.isEmpty(row + direction, col + i))
            {
                continue;
            }
        }

        if(((row + direction) == rowDest) && ((col + i) == colDest))
        {
            return true;
        }
    }

    if(color == White)
    {
        if(row == 1)
        {
            if((rowDest == 3) && (col == colDest))
            {
                if(!chessBoard.isEmpty(2, col) ||
                        !chessBoard.isEmpty(3, col))
                {
                    return false;
                }

                return true;
            }
        }
    }

    if(color == Black)
    {
        if(row == 6)
        {
            if((rowDest == 4) && (col == colDest))
            {
                if(!chessBoard.isEmpty(5, col) ||
                        !chessBoard.isEmpty(4, col))
                {
                    return false;
                }

                return true;
            }
        }
    }

    return false;
}
