#ifndef PGNGameResult_h
#define PGNGameResult_h

#include <fstream>
#include <string>

namespace pgn
{
class GameResult
{
public:

    GameResult();
    GameResult(std::string s);
    GameResult(const GameResult& src);

    GameResult& operator = (const GameResult& src);
    bool operator == (const GameResult& src) const;
    bool operator != (const GameResult& src) const;

    bool isWhiteWin() const;
    bool isBlackWin() const;
    bool isDrawn() const;
    bool isUnknown() const;

    friend std::ostream& operator << ( std::ostream& os, const GameResult& src);

private:

    char result_;
};

std::ostream& operator << ( std::ostream& os, const pgn::GameResult& src );
};

#endif 

