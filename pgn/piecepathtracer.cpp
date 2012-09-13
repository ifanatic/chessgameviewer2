#include "piecepathtracer.h"

#include "gameplayer.h"

#include <iostream>

PiecePathTracer::PiecePathTracer()
{
}

vector<ChessPosition> PiecePathTracer::path(const vector<Ply>& moves,
                 int currentMove,
                 const ChessPosition &piecePos)
{
    GamePlayer player;
    player.setMoves(moves);

    ChessPosition interestedPos = piecePos;

    vector<ChessPosition> result;

    result.push_back(piecePos);

    for(; currentMove; --currentMove)
    {
        player.goToMove(currentMove);

        if(player.chessBoard().lastDst().col == interestedPos.col &&
                player.chessBoard().lastDst().row == interestedPos.row)
        {
            result.push_back(player.chessBoard().lastSrc());
            interestedPos = player.chessBoard().lastSrc();
        }
    }

    return result;
}
