
#ifndef PGNParser_h
#define PGNParser_h

#include <string>

#include "gamevollection.h"

namespace pgn
{
class Parser
{
public:

    Parser():plyCount_(0),moveCount_(0),gameCount_(0), _errorsCount(0) {}

    bool getGameCollection(std::string::const_iterator &itr1,
                           const std::string::const_iterator &itr2, pgn::GameCollection &out);
    pgn::Game* getGame(std::string::const_iterator &itr1,
                       const std::string::const_iterator &itr2);
    bool getMoveList(std::string::const_iterator &itr1,
                     const std::string::const_iterator &itr2, pgn::MoveList &out);
    pgn::Move* getMove(std::string::const_iterator &itr1,
                       const std::string::const_iterator &itr2);
    pgn::Ply* getPly(std::string::const_iterator &itr1,
                     const std::string::const_iterator &itr2);
    bool getTagList(std::string::const_iterator &itr1,
                    const std::string::const_iterator &itr2, pgn::TagList &out);
    bool getTag(std::string::const_iterator &itr1,
                const std::string::const_iterator &itr2, pgn::Tag &out);
    bool getGameResult(std::string::const_iterator &itr1,
                       const std::string::const_iterator &itr2, pgn::GameResult &out);
    bool getComment(std::string::const_iterator &itr1,
                    const std::string::const_iterator &itr2, pgn::CommentText &out);
    bool getMoveNumber(std::string::const_iterator &itr1,
                       const std::string::const_iterator &itr2, std::string &out, int &dotsCount);

    int getGlyph(std::string::const_iterator &itr1, const std::string::const_iterator &itr2);

    bool getVariation(std::string::const_iterator &itr1,
                      const std::string::const_iterator &itr2, pgn::MoveList &out);

    void checkForVariations(std::string::const_iterator &itr1, const std::string::const_iterator &itr2);


    unsigned long plyCount() const { return plyCount_; }
    unsigned long moveCount() const { return moveCount_; }
    unsigned long gameCount() const { return gameCount_; }
    unsigned long getErrorsCount() const { return _errorsCount; }
    bool hasErrors() const { return _errorsCount > 0; }

private:

    static void skipBlanks(std::string::const_iterator &itr1, const std::string::const_iterator &end);

    unsigned long plyCount_;
    unsigned long moveCount_;
    unsigned long gameCount_;
    unsigned long _errorsCount;

};
}
#endif // PGNParser_h
