#ifndef PGNTag_h
#define PGNTag_h

#include <fstream>
#include <string>

namespace pgn
{
class Tag
{
public:

    Tag();
    Tag(const Tag& src);
    Tag(const std::string name, const std::string value);

    virtual ~Tag();

    Tag& operator = (const Tag& other);
    bool operator == (const Tag& other) const;
    bool operator != (const Tag& other) const;
    bool operator == (const std::string& tagName) const;
    bool operator != (const std::string& tagName) const;

    std::string name() const;
    std::string value() const;

    friend std::ostream& operator << (std::ostream& os, const Tag& src);

private:

    struct TagData *hdata;
};

std::ostream& operator << ( std::ostream& os, const pgn::Tag& src );

};

#endif

