#ifndef PGNMove_h
#define PGNMove_h

#include <fstream>
#include "ply.h"

namespace pgn 
{
class Move
{
public:

    Move(const Move& src);
    Move(const Ply *white, const Ply *black, int number);

    virtual ~Move();

    Move& operator = (const Move& src);
    bool operator == (const Move& src) const;
    bool operator != (const Move& src) const;

    bool isCheckMate() const;
    Ply* white() const;
    Ply* black() const;

    friend std::ostream& operator << ( std::ostream& os, const Move& src);

private:

    struct MoveData *hdata;
};
};

#endif 

