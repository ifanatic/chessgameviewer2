#include <sstream>
#include "commenttext.h"

namespace pgn
{
struct CommentTextData
{
    std::string comment;
};
};

pgn::CommentText::CommentText() 
{
    hdata = new pgn::CommentTextData;
}

pgn::CommentText::CommentText(const std::string &text) 
{
    hdata = new pgn::CommentTextData;
    hdata->comment = text;
}

pgn::CommentText::CommentText(const pgn::CommentText& src) 
{
    hdata = new pgn::CommentTextData;
    hdata->comment = src.hdata->comment;
}

pgn::CommentText::~CommentText() 
{
    delete hdata;
}

pgn::CommentText& pgn::CommentText::operator = (const pgn::CommentText& src) 
{
    if (&src == this)
        return(*this);

    hdata->comment = src.hdata->comment;

    return *this;
}

bool pgn::CommentText::operator == (const pgn::CommentText& src) const
{
    return (hdata->comment == src.hdata->comment);
}

bool pgn::CommentText::operator != (const pgn::CommentText& src) const
{
    return !(*this == src);
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::CommentText& src ) 
{
    if (src.hdata->comment == "")
        return os;

    os << " {" << src.hdata->comment << "}";

    return os;
}

