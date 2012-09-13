#ifndef PGNMoveList_h
#define PGNMoveList_h

#include <fstream>
#include <vector>
#include <set>
#include "move.h"
#include "gameresult.h"

namespace pgn
{
class MoveList
{
public:

    class iterator;
    friend class iterator;

    MoveList();
    MoveList(const MoveList& src);

    virtual ~MoveList();

    MoveList& operator = (const MoveList& src);
    bool operator == (const MoveList& src) const;
    bool operator != (const MoveList& src) const;
    Move operator [] (int idx);

    void insert(const Move& src);
    bool find(const Move& src) const;
    int size() const;
    iterator begin() const;
    iterator end() const;
    void bindComment(const CommentText &ct);

    friend std::ostream& operator << ( std::ostream& os, const MoveList& src);

private:

    struct MoveListData *hdata;

};


class MoveList::iterator
{
public:

    iterator();
    iterator(const MoveList &ml);
    iterator(const MoveList &ml, int);
    iterator(const iterator&);
    ~iterator();
    iterator& operator = (const iterator&);
    iterator& operator ++ ();
    iterator& operator ++ (int);
    Move* operator -> () const;
    const Move& operator * () const;
    bool operator == (const iterator&) const;
    bool operator != (const iterator&) const;

private:

    struct iteratorData *hdata;
};

};

#endif 

