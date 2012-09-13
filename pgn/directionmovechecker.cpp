#include "directionmovechecker.h"

#include <iostream>

DirectionMoveChecker::DirectionMoveChecker()
{
    _directions = NULL;
    _directionsCount = 0;
}

DirectionMoveChecker::~DirectionMoveChecker()
{
    if(_directions == NULL)
    {
        return;
    }

    for(int i = 0; i < _directionsCount; ++i)
    {
        delete _directions[i];
    }

    delete _directions;
}


bool DirectionMoveChecker::canMoveTo(int row, int col, PieceColor color,
                           int rowDest, int colDest,
                           const ChessBoard& chessBoard)
{
    int newRow = row;
    int newCol = col;

//    std::cout << "row: " << newRow << ", col: " << newCol << std::endl;
//    std::cout << "destRow: " << rowDest << ", destCol: " << colDest << std::endl;

    for(int j = 0; j < _directionsCount; ++j)
    {
        for(int i = 1; i < 8; ++i)
        {
            newRow = row + i * _directions[j][1];
            newCol = col + i * _directions[j][0];

//            std::cout << "NewRow: " << newRow << ", NewCol: " << newCol << std::endl;

            if(!BasicMoveChecker::canMoveTo(newRow, newCol, color, rowDest, colDest, chessBoard))
            {
                break;
            }

            if((newRow == rowDest) && (newCol == colDest))
            {
                return true;
            }

            if(!chessBoard.isEmpty(newRow, newCol))
            {
                break;
            }
        }
    }

    return false;
}
