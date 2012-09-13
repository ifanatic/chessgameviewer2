#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "ply.h"
#include <vector>
#include <algorithm>
#include <iterator>

#include "chessboard.h"

using namespace std;

class GamePlayer
{
private:
    ChessBoard _chessBoard;
    std::vector<pgn::Ply> _moves;
    int _currentPos;

public:
    GamePlayer();

    void setMoves(const std::vector<pgn::Ply>& moves)
    {
        _moves.clear();
        std::copy(moves.begin(), moves.end(), std::back_inserter(_moves));
    }

    void goToBegin();
    bool goToMove(int index);
    bool goToEnd();
    bool prev();
    bool next();

    int movesCount() const { return _moves.size();}

    int getCurrentPos() const { return _currentPos; }
    PieceColor currentColor() const { return ((_currentPos % 2 == 0) ? White : Black); }

    ChessBoard& chessBoard() { return _chessBoard; }
    const std::vector<pgn::Ply>& getMoves() const
    {
        return _moves;
    }
};

#endif // GAMEPLAYER_H
