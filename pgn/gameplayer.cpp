#include "gameplayer.h"

GamePlayer::GamePlayer()
{
}

void GamePlayer::goToBegin()
{
    _chessBoard.clear();
    _chessBoard.init();
    _currentPos = 0;
}

bool GamePlayer::goToMove(int index)
{
    goToBegin();

    if(index < 0)
    {
        return false;
    }
    if(index >= (int)_moves.size())
    {
        return false;
    }

    int currentIndex = 0;
    PieceColor currentColor = White;

    while((currentIndex != index) && (currentIndex < (int)_moves.size()))
    {
        _chessBoard.makeMove(currentColor, _moves[currentIndex]);
        ++_currentPos;
        ++currentIndex;
        currentColor = (currentColor == White) ? Black : White;
    }

    return true;
}

bool GamePlayer::goToEnd()
{
    return goToMove((int)_moves.size() - 1);
}

bool GamePlayer::prev()
{
    return goToMove(_currentPos - 1);
}

bool GamePlayer::next()
{
    return goToMove(_currentPos + 1);
}
