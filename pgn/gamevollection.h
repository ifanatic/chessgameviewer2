#ifndef PGNGameCollection_h
#define PGNGameCollection_h

#include <fstream>
#include <vector>
#include "game.h"

namespace pgn
{
class GameCollection
{
public:

    class iterator;
    friend class iterator;

    GameCollection();
    GameCollection(const GameCollection& src);

    virtual ~GameCollection();

    GameCollection& operator = (const GameCollection& src);
    bool operator == (const GameCollection& src) const;
    bool operator != (const GameCollection& src) const;
    virtual Game operator [] (const int idx) const;

    void insert(const Tag& src); // deprecated
    void erase(const Tag& src); // deprecated
    void sort(const Tag &key); // deprecated
    void insert(const Game& src);
    void erase(const Game& src);
    int size() const;
    void clear();
    iterator begin();
    iterator end();

    friend std::ostream& operator << ( std::ostream& os, const GameCollection& src);
    friend std::istream& operator >> ( std::istream& is, GameCollection& src);

private:

    struct GameCollectionData *hdata;
};

class GameCollection::iterator
{
public:

    iterator();
    iterator(const GameCollection &ml);
    iterator(const GameCollection &ml, int);
    iterator(const iterator&);
    ~iterator();
    iterator& operator = (const iterator&);
    iterator& operator ++ ();
    iterator& operator ++ (int);
    Game* operator -> () const;
    const Game& operator * () const;
    bool operator == (const iterator&) const;
    bool operator != (const iterator&) const;

private:

    struct iteratorData *hdata;
};
};

#endif 

