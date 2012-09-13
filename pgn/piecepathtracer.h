#ifndef PIECEPATHTRACER_H
#define PIECEPATHTRACER_H

#include <vector>

#include "chessboard.h"

using pgn::Ply;
using namespace std;

class PiecePathTracer
{
public:
    PiecePathTracer();

    vector<ChessPosition> path(const vector<Ply>& moves,
                     int currentMove,
                     const ChessPosition& piecePos);
};

#endif // PIECEPATHTRACER_H
