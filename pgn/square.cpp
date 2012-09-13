#include <sstream>
#include <iostream>
#include "square.h"

pgn::Square::Square()
{
    col_ = 0;
    row_ = 0;

}

pgn::Square::Square(char col, char row)
    :col_(col),row_(row)
{

}

pgn::Square::Square(const pgn::Square& src)
    :col_(src.col_),row_(src.row_)
{

}

pgn::Square::~Square()
{ 

}

pgn::Square& pgn::Square::operator = (const pgn::Square& src)
{
    if (&src == this)
        return (*this);

    col_ = src.col_;
    row_ = src.row_;

    return(*this);
}

bool pgn::Square::operator == (const pgn::Square& src) const
{
    return (col_ == src.col_) && (row_ == src.row_);
}

char pgn::Square::col() const
{
    return col_;
}

char pgn::Square::row() const
{
    return row_;
}

bool pgn::Square::operator != (const pgn::Square& src) const 
{
    return !(src == *this);
}


int pgn::Square::colIndex() const
{
    return (col_ - 'a');
}
int pgn::Square::rowIndex() const
{
    return (row_ - '1');
}

