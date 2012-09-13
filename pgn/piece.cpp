#include <cstdio>
#include <cassert>
#include <sstream>
#include <iostream>
#include "piece.h"

pgn::Piece::Piece()
{
    id_='p';
}

pgn::Piece::Piece(const pgn::Piece &src)
{
    id_ = src.id_;
}

pgn::Piece& pgn::Piece::operator = (const pgn::Piece& src) 
{
    if (&src == this)
        return(*this);

    id_ = src.id_;

    return *this;
}

pgn::Piece::Piece(const char id)
    :id_(id)
{

}

bool pgn::Piece::operator == (const pgn::Piece& src) const
{
    return id_ == src.id_;
}

bool pgn::Piece::operator != (const pgn::Piece& src) const 
{
    return !(src == *this);
}

char pgn::Piece::id() const 
{ 
    return id_;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::Piece& src ) 
{
    if (src.id_ != 'p')
        os << src.id_;
    return os;
}

