#ifndef GAMEFINDER_H
#define GAMEFINDER_H

#include <vector>

#include <QSqlQuery>
#include <QString>

#include "game.h"
#include "tag.h"

using namespace pgn;

class GameFinder
{
private:
    std::vector<QString> _tagNames;

    pgn::Tag getTagByName(const QString& tagName, const QSqlQuery& query);

    void getMoves(int gameId, MoveList& moves);

public:
    GameFinder();

    pgn::Game getGameById(int gameId);
};

#endif // GAMEFINDER_H
