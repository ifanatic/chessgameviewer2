#ifndef MOVECHECKERSREPOSITORY_H
#define MOVECHECKERSREPOSITORY_H

#include "chessboard.h"
#include "basicmovechecker.h"
#include "utils.h"

class MoveCheckersRepository
{
private:

    BasicMoveChecker* _checkers[7];

    static MoveCheckersRepository* _instance;

    MoveCheckersRepository();


public:

    static MoveCheckersRepository* instance()
    {
        if(_instance == NULL)
        {
            _instance = new MoveCheckersRepository();
        }

        return _instance;
    }

    BasicMoveChecker* getCheckerByType(PieceType type)
    {
        return _checkers[(int)type];
    }

    BasicMoveChecker* getCheckerByChar(char c)
    {
        return getCheckerByType(convertCharToType(c));
    }
};

#endif // MOVECHECKERSREPOSITORY_H
