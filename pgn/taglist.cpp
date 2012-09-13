#include <sstream>
#include <iostream>
#include <stdexcept>
#include "taglist.h"

namespace pgn 
{
struct TagListData
{
    std::vector<pgn::Tag> tags;
};
};

pgn::TagList::TagList() 
{
    hdata = new pgn::TagListData;
}

pgn::TagList::TagList(const pgn::TagList& src) 
{
    hdata = new pgn::TagListData;
    hdata->tags = src.hdata->tags;
}

pgn::TagList::~TagList() 
{
    delete hdata;
}

pgn::TagList& pgn::TagList::operator = (const pgn::TagList& src) 
{
    if (&src == this)
        return(*this);

    hdata->tags = src.hdata->tags;

    return *this;
}

void pgn::TagList::insert(const pgn::Tag& src)
{
    for (std::vector<pgn::Tag>::iterator it=hdata->tags.begin(); it != hdata->tags.end(); it++)
    {
        if (*it == src.name())
        {
            (*it) = src;
            return;
        }
    }
    hdata->tags.push_back(src);
}

void pgn::TagList::erase(const pgn::Tag& src)
{
    for (std::vector<pgn::Tag>::iterator it=hdata->tags.begin(); it != hdata->tags.end(); it++)
    {
        if (*it == src.name())
        {
            hdata->tags.erase(it);
        }
    }
}

int pgn::TagList::size() const
{
    return hdata->tags.size();
}

bool pgn::TagList::operator == (const pgn::TagList& src) const
{
    if (hdata->tags.size() != src.hdata->tags.size())
        return false;

    for (int i=0; i<(int)src.hdata->tags.size(); i++)
    {
        if (hdata->tags[i] != src.hdata->tags[i])
            return false;
    }

    return true;
}

pgn::Tag pgn::TagList::operator [] (const std::string& key) const
{
    for (std::vector<pgn::Tag>::iterator it=hdata->tags.begin(); it != hdata->tags.end(); it++)
    {
        if (it->name() == key)
        {
            return *it;
        }
    }

    throw std::runtime_error("Tag not found in TagList");
}

bool pgn::TagList::find(std::string key) const
{
    for (std::vector<pgn::Tag>::iterator it=hdata->tags.begin(); it != hdata->tags.end(); it++)
    {
        if (it->name() == key)
        {
            return true;
        }
    }

    return false;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::TagList& src ) 
{
    for (int i=0; i<(int)src.hdata->tags.size(); i++)
    {
        os << src.hdata->tags[i];
    }

    return os;
}

bool pgn::TagList::operator != (const pgn::TagList& src) const 
{ 
    return !(*this == src);
}

pgn::TagList::iterator pgn::TagList::begin() const
{
    pgn::TagList::iterator itr(*this);
    return itr;
}

pgn::TagList::iterator pgn::TagList::end() const
{
    pgn::TagList::iterator itr(*this,0);
    return itr;
}

//
// iterator
//

namespace pgn
{
struct iteratorData
{
    std::vector<pgn::Tag>::iterator it;
};
};


pgn::TagList::iterator::iterator()
{
    hdata = new iteratorData;
}

pgn::TagList::iterator::iterator(const pgn::TagList &tl)
{
    hdata = new iteratorData;
    hdata->it = tl.hdata->tags.begin();
}

pgn::TagList::iterator::iterator(const pgn::TagList &tl, int)
{
    hdata = new iteratorData;
    hdata->it = tl.hdata->tags.end();
}

pgn::TagList::iterator::iterator(const pgn::TagList::iterator &other)
{
    hdata = new iteratorData;
    hdata->it = other.hdata->it;
}

pgn::TagList::iterator::~iterator()
{
    delete hdata;
}

pgn::TagList::iterator& pgn::TagList::iterator::operator = (const pgn::TagList::iterator& other) 
{
    if (&other == this)
        return *this;

    hdata->it = other.hdata->it;

    return *this;
}

pgn::TagList::iterator& pgn::TagList::iterator::operator ++ ()
{
    hdata->it++;
    return (*this);
}

pgn::TagList::iterator& pgn::TagList::iterator::operator ++ (int)
{
    return (operator ++ ());
}

pgn::Tag* pgn::TagList::iterator::operator -> () const
{
    return &(*hdata->it);
}

const pgn::Tag& pgn::TagList::iterator::operator * () const
{
    return *(hdata->it);
}

bool pgn::TagList::iterator::operator == (const pgn::TagList::iterator& other) const
{
    return (hdata->it == other.hdata->it);
}

bool pgn::TagList::iterator::operator != (const pgn::TagList::iterator& other) const
{
    return (!((*this) == other));
}

