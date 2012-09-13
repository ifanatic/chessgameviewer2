#include <sstream>
#include <iostream>
#include "tag.h"

namespace pgn
{
struct TagData
{
    std::string tagName;
    std::string tagValue;
};
};

pgn::Tag::Tag() 
{
    hdata = new pgn::TagData;

}

pgn::Tag::Tag(const pgn::Tag& src) 
{
    hdata = new pgn::TagData;
    hdata->tagName = src.hdata->tagName;
    hdata->tagValue = src.hdata->tagValue;

}

pgn::Tag::Tag(const std::string name, const std::string value)
{
    hdata = new pgn::TagData;
    hdata->tagName = name;
    hdata->tagValue = value;
}

pgn::Tag::~Tag() 
{
    delete hdata;
}

pgn::Tag& pgn::Tag::operator = (const pgn::Tag& src) 
{
    if (&src == this)
        return(*this);

    hdata->tagName = src.hdata->tagName;
    hdata->tagValue = src.hdata->tagValue;

    return *this;
}

bool pgn::Tag::operator == (const pgn::Tag& other) const
{
    if (hdata->tagName != other.hdata->tagName)
        return false;
    if (hdata->tagValue != other.hdata->tagValue)
        return false;

    return true;
}

bool pgn::Tag::operator == (const std::string& tagName) const
{
    return (hdata->tagName == tagName);
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::Tag& src ) 
{
    os << "[" << src.hdata->tagName << " \"" << src.hdata->tagValue << "\"]" << std::endl;
    return os;
}

bool pgn::Tag::operator != (const pgn::Tag& src) const 
{ 
    return !(*this == src);
}

bool pgn::Tag::operator != (const std::string& other) const 
{ 
    return !(*this == other);
}

std::string pgn::Tag::name() const 
{ 
    return hdata->tagName;
}

std::string pgn::Tag::value() const 
{ 
    return hdata->tagValue;
}

