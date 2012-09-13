#include <iostream>
#include <sstream>
#include <stdexcept>
#include "move.h"

namespace pgn
{
struct MoveData
{
    bool complete;
    int number;
    pgn::Ply *white;
    pgn::Ply *black;
};
};

pgn::Move::Move(const pgn::Move& src) 
{
    hdata = new pgn::MoveData;

    hdata->complete = src.hdata->complete;
    hdata->number = src.hdata->number;
    if (src.hdata->white)
        hdata->white = new pgn::Ply(*(src.hdata->white));
    else
        hdata->white = 0;
    if (src.hdata->black)
        hdata->black = new pgn::Ply(*(src.hdata->black));
    else
        hdata->black = 0;
}

pgn::Move& pgn::Move::operator = (const pgn::Move& src) 
{
    if (&src == this)
        return(*this);

    hdata->complete = src.hdata->complete;
    hdata->number = src.hdata->number;
    if (src.hdata->white)
    {
        delete hdata->white;
        hdata->white = new pgn::Ply(*(src.hdata->white));
    }
    else
        hdata->white = 0;
    if (src.hdata->black)
    {
        delete hdata->black;
        hdata->black = new pgn::Ply(*(src.hdata->black));
    }
    else
        hdata->black = 0;

    return *this;
}

pgn::Move::Move(const pgn::Ply *white, const pgn::Ply *black, int number)
{
    hdata = new pgn::MoveData;

    hdata->number = number;
    if (white)
        hdata->white = new Ply(*white);
    else
        hdata->white = 0;
    if (black)
        hdata->black = new Ply(*black);
    else
        hdata->black = 0;

    hdata->complete = (hdata->white && hdata->black);
}

pgn::Move::~Move() 
{

    delete hdata->white; hdata->white = 0;
    delete hdata->black; hdata->black = 0;
    delete hdata; hdata = 0;
}

bool pgn::Move::operator == (const pgn::Move& src) const
{
    if (hdata->complete != src.hdata->complete)
        return false;
    if (hdata->number != src.hdata->number)
        return false;
    if ((hdata->white == 0) && (src.hdata->white != 0))
        return false;
    else if ((hdata->white != 0) && (src.hdata->white == 0))
        return false;
    else if ((hdata->white != 0) && (src.hdata->white != 0) &&
             *(hdata->white) != *(hdata->white))
        return false;
    if ((hdata->black == 0) && (src.hdata->black != 0))
        return false;
    else if ((hdata->black != 0) && (src.hdata->black == 0))
        return false;
    else if ((hdata->black != 0) && (src.hdata->black != 0) &&
             *(hdata->black) != *(hdata->black))
        return false;

    return true;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::Move& src ) 
{
    if (src.hdata->white && src.hdata->black)
        os << src.hdata->number << ". " << *(src.hdata->white) << " " << *(src.hdata->black);
    else if (src.hdata->white)
        os << src.hdata->number << ". " << *(src.hdata->white);
    else if (src.hdata->black)
        os << src.hdata->number << "... " << *(src.hdata->black);
    return os;
}

bool pgn::Move::isCheckMate() const
{
    return ((hdata->white && hdata->white->isCheckMate()) || (hdata->black && hdata->black->isCheckMate()));
}

bool pgn::Move::operator != (const pgn::Move& src) const 
{ 
    return !(*this == src);
}

pgn::Ply* pgn::Move::white() const 
{ 
    return hdata->white;
} 

pgn::Ply* pgn::Move::black() const 
{ 
    return hdata->black;
}

