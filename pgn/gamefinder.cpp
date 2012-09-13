#include "gamefinder.h"

#include <QSqlRecord>
#include <QVariant>

#include "taglist.h"
#include "movelist.h"
#include "move.h"
#include "ply.h"
#include "gameresult.h"

#include <iostream>

using namespace pgn;

pgn::Tag GameFinder::getTagByName(const QString& tagName, const QSqlQuery& query)
{
    QSqlRecord record = query.record();
    int idx = record.indexOf(tagName);

    QString tagNameCpy = tagName;

    tagNameCpy = tagNameCpy.left(1).toUpper() + tagNameCpy.mid(1);

    return Tag(tagNameCpy.toStdString(),
               query.value(idx).toString().toStdString());
}

void GameFinder::getMoves(int gameId, MoveList &moves)
{
    QSqlQuery query;
    query.prepare("SELECT notation FROM moves WHERE game_id = ? ORDER BY move_number");
    query.bindValue(0, gameId);
    query.exec();

    int notationIdx = query.record().indexOf("notation");
    int currentMoveNumber = 1;

    QString whiteMove;
    QString blackMove;

    while(query.next())
    {
        whiteMove = query.value(notationIdx).toString();
        Ply whitePly(whiteMove.toStdString());

        if(!query.next())
        {
            Move move(&whitePly, NULL, currentMoveNumber);
            moves.insert(move);
            break;
        }
        else
        {
            blackMove = query.value(notationIdx).toString();
            Ply blackPly(blackMove.toStdString());
            Move move(&whitePly, &blackPly, currentMoveNumber);
            moves.insert(move);
        }

        ++currentMoveNumber;
    }
}

GameFinder::GameFinder()
{    
    _tagNames.push_back("event");
    _tagNames.push_back("site");
    _tagNames.push_back("date");
    _tagNames.push_back("round");
    _tagNames.push_back("white");
    _tagNames.push_back("black");
    _tagNames.push_back("result");
    _tagNames.push_back("eco");
}

pgn::Game GameFinder::getGameById(int gameId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM games WHERE id = ?");
    query.bindValue(0, QVariant(gameId));

    query.exec();

    TagList tags;
    MoveList moves;

    while(query.next())
    {
        for(size_t i = 0; i < _tagNames.size(); ++i)
        {
            tags.insert(getTagByName(_tagNames[i], query));
        }

        break;
    }

    getMoves(gameId, moves);

    GameResult gameResult(tags["Result"].value());

    return Game(tags, moves, gameResult);
}
