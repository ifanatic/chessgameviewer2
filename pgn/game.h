#ifndef PGNGame_h
#define PGNGame_h

#include <fstream>
#include "gameresult.h"
#include "taglist.h"
#include "movelist.h"

namespace pgn
{
class Game
{
public:

    Game(const TagList &tl, const MoveList &ml, const GameResult &gr);
    Game(const Game& src);

    virtual ~Game();

    Game& operator = (const Game& src);
    bool operator == (const Game& src) const;
    bool operator != (const Game& src) const;

    TagList& tags() const;
    MoveList& moves() const;
    std::string date() const;
    std::string white() const;
    std::string black() const;
    GameResult result() const;
    void bindBeforeGameComment(const CommentText &ct);
    void bindAfterGameComment(const CommentText &ct);

    friend std::ostream& operator << ( std::ostream& os, const Game& src);

private:

    struct GameData *hdata;
};
};

#endif 

