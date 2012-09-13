#ifndef PGNSquare_h
#define PGNSquare_h

#include <string>

namespace pgn 
{
class Square
{
public:

    Square();
    Square(char col, char row);
    Square(const Square& src);

    virtual ~Square();

    Square& operator = (const Square& src);
    bool operator == (const Square& src) const;
    bool operator != (const Square& src) const;

    char col() const;
    char row() const;
    int colIndex() const;
    int rowIndex() const;

private:

    char col_;
    char row_;

};
};

#endif 

