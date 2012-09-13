#ifndef PGNPiece_h
#define PGNPiece_h

namespace pgn
{
class Piece
{
public:

    static const Piece Pawn() { return 'p'; }
    static const Piece Knight() { return 'N'; }
    static const Piece Bishop() { return 'B'; }
    static const Piece Rook() { return 'R'; }
    static const Piece Queen() { return 'Q'; }
    static const Piece King() { return 'K'; }

    Piece();
    Piece(const Piece &src);
    Piece(const char id);

    Piece& operator = (const Piece& src);
    bool operator == (const Piece& src) const;
    bool operator != (const Piece& src) const;

    char id() const;

    friend std::ostream& operator << ( std::ostream& os, const pgn::Piece& src);

private:

    char id_;
};
std::ostream& operator << ( std::ostream& os, const pgn::Piece& src );
};

#endif 

