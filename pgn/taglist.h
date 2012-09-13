#ifndef PGNTagList_h
#define PGNTagList_h

#include <fstream>
#include <vector>
#include "tag.h"

namespace pgn
{
class TagList
{
public:

    class iterator;
    friend class iterator;

    TagList();
    TagList(const TagList& src);

    virtual ~TagList();

    TagList& operator = (const TagList& src);
    bool operator == (const TagList& src) const;
    bool operator != (const TagList& src) const;
    Tag operator [] (const std::string& tagName) const;

    bool find(std::string tagName) const;
    void insert(const Tag& src);
    void erase(const Tag& src);
    int size() const;
    iterator begin() const;
    iterator end() const;

    friend std::ostream& operator << ( std::ostream& os, const TagList& src);
    friend std::istream& operator >> ( std::istream& is, TagList& target);

private:

    struct TagListData *hdata;
};

class TagList::iterator
{
public:

    iterator();
    iterator(const TagList &tl);
    iterator(const TagList &tl, int);
    iterator(const iterator&);
    ~iterator();
    iterator& operator = (const iterator&);
    iterator& operator ++ ();
    iterator& operator ++ (int);
    Tag* operator -> () const;
    const Tag& operator * () const;
    bool operator == (const iterator&) const;
    bool operator != (const iterator&) const;

private:

    struct iteratorData *hdata;
};
};

#endif 

