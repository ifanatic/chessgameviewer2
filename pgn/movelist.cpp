#include <sstream>
#include <iostream>
#include "movelist.h"

#include <iomanip>

namespace pgn
{
struct MoveListData
{
    std::vector<pgn::Move> mosse;
    pgn::CommentText comment;
};
};

pgn::MoveList::MoveList() 
{
    hdata = new pgn::MoveListData;
}

pgn::MoveList::MoveList(const pgn::MoveList& src) 
{
    hdata = new pgn::MoveListData;
    hdata->mosse = src.hdata->mosse;
}

pgn::MoveList::~MoveList() 
{
    delete hdata;
}

pgn::MoveList& pgn::MoveList::operator = (const pgn::MoveList& src) 
{
    if (&src == this)
        return(*this);

    hdata->mosse = src.hdata->mosse;

    return *this;
}

void pgn::MoveList::insert(const pgn::Move& src)
{
    hdata->mosse.push_back(src);
}

bool pgn::MoveList::operator == (const pgn::MoveList& src) const
{
    if (hdata->mosse.size() != src.hdata->mosse.size())
        return false;

    for (int i=0; i<(int)src.hdata->mosse.size(); i++)
    {
        if (hdata->mosse[i] != src.hdata->mosse[i])
            return false;
    }

    return true;
}

bool pgn::MoveList::find(const pgn::Move& src) const
{
    for (int i=0; i<(int)hdata->mosse.size(); i++)
    {
        if (hdata->mosse[i] == src)
            return true;
    }

    return false;
}

void pgn::MoveList::bindComment(const CommentText &ct)
{
    hdata->comment = ct;
}


#include <streambuf>
class formatbuf: public std::streambuf
{
public:
    formatbuf(int length, std::streambuf* sbuf);
    ~formatbuf();

private:
    int overflow(int c);

    std::streambuf* m_sbuf;
};

formatbuf::formatbuf(int length, std::streambuf* sbuf)
{
    m_sbuf = sbuf;
    char *buf = new char [length + 1];
    setp(buf, buf + length);
}

formatbuf::~formatbuf()
{
    m_sbuf->sputn(pbase(), pptr() - pbase());
    m_sbuf->sputc('\n');
    delete [] pbase();
}

int formatbuf::overflow(int c)
{

    if (pptr() != epptr())
        return 0;
    else
    {
        *epptr() = c;

        char *ptr = epptr();

        while ((ptr != pbase()) && (*ptr != '\n'))
            --ptr;

        if (ptr == pbase()) // no newlines in the text
        {
            ptr = epptr();
            while ((ptr != pbase()) && (*ptr != ' '))
                --ptr;

            if (ptr == pbase())
                ptr = epptr();
        }

        m_sbuf->sputn(pbase(), ptr - pbase());
        m_sbuf->sputc('\n');


        if ((*ptr == ' ') || (*ptr == '\n'))
            ++ptr;

        setp(pbase(), epptr());
        sputn(ptr, epptr() + 1 - ptr);
    }
    return c;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::MoveList& src ) 
{
    formatbuf fmt(80, os.rdbuf());
    std::ostream out(&fmt);
    for (int i=0; i<(int)src.hdata->mosse.size(); i++)
    {
        out << src.hdata->mosse[i] << " ";
    }

    return os;
}

bool pgn::MoveList::operator != (const pgn::MoveList& src) const 
{ 
    return !(*this == src);
}

int pgn::MoveList::size() const 
{ 
    return hdata->mosse.size();
}

pgn::Move pgn::MoveList::operator [] (int idx) 
{ 
    return hdata->mosse[idx];
}		

pgn::MoveList::iterator pgn::MoveList::begin() const
{
    pgn::MoveList::iterator itr(*this);
    return itr;
}

pgn::MoveList::iterator pgn::MoveList::end() const
{
    pgn::MoveList::iterator itr(*this,0);
    return itr;
}


namespace pgn
{
struct iteratorData
{
    std::vector<pgn::Move>::iterator it;
};
};


pgn::MoveList::iterator::iterator()
{
    hdata = new iteratorData;
}

pgn::MoveList::iterator::iterator(const pgn::MoveList &ml)
{
    hdata = new iteratorData;
    hdata->it = ml.hdata->mosse.begin();
}

pgn::MoveList::iterator::iterator(const pgn::MoveList &ml, int)
{
    hdata = new iteratorData;
    hdata->it = ml.hdata->mosse.end();
}

pgn::MoveList::iterator::iterator(const pgn::MoveList::iterator &other)
{
    hdata = new iteratorData;
    hdata->it = other.hdata->it;
}

pgn::MoveList::iterator::~iterator()
{
    delete hdata;
}

pgn::MoveList::iterator& pgn::MoveList::iterator::operator = (const pgn::MoveList::iterator& other) 
{
    if (&other == this)
        return *this;

    hdata->it = other.hdata->it;

    return *this;
}

pgn::MoveList::iterator& pgn::MoveList::iterator::operator ++ ()
{
    hdata->it++;
    return (*this);
}

pgn::MoveList::iterator& pgn::MoveList::iterator::operator ++ (int)
{
    return (operator ++ ());
}

pgn::Move* pgn::MoveList::iterator::operator -> () const
{
    return &(*hdata->it);
}

const pgn::Move& pgn::MoveList::iterator::operator * () const
{
    return *(hdata->it);
}

bool pgn::MoveList::iterator::operator == (const pgn::MoveList::iterator& other) const
{
    return  (hdata->it == other.hdata->it);
}

bool pgn::MoveList::iterator::operator != (const pgn::MoveList::iterator& other) const
{
    return (!((*this) == other));
}

