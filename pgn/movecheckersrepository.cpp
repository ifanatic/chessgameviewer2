#include "movecheckersrepository.h"

#include "bishopmovechecker.h"
#include "kingmovechecker.h"
#include "knightmovechecker.h"
#include "pawnmovechecker.h"
#include "queenmovechecker.h"
#include "rookmovechecker.h"

MoveCheckersRepository* MoveCheckersRepository::_instance = NULL;

MoveCheckersRepository::MoveCheckersRepository()
{
    _checkers[0] = NULL;
    _checkers[1] = new PawnMoveChecker();
    _checkers[2] = new KnightMoveChecker();
    _checkers[3] = new BishopMoveChecker();
    _checkers[4] = new RookMoveChecker();
    _checkers[5] = new QueenMoveChecker();
    _checkers[6] = new KingMoveChecker();
}
