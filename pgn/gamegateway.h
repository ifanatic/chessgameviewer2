#ifndef GAMEGATEWAY_H
#define GAMEGATEWAY_H

#include <vector>

#include <QString>

#include "game.h"
#include "ply.h"

using namespace std;
using namespace pgn;

class GameGateway
{
private:
    struct MoveData
    {
        QString notation;
        int moveNumber;
        QString fen;
    };

public:
    GameGateway();

    bool insertGame(const pgn::Game& game);
};

#endif // GAMEGATEWAY_H
