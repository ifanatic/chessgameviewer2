#ifndef PGNPly_h
#define PGNPly_h

#include <fstream>
#include <string>
#include <vector>
#include "piece.h"
#include "square.h"
#include "commenttext.h"

namespace pgn
{
class MoveList;
class Ply
{
public:

    Ply(const Ply& src);
    Ply(const std::string &ply_text);

    virtual ~Ply();

    Ply& operator = (const Ply& src);
    bool operator == (const Ply& src) const;
    bool operator != (const Ply& src) const;

    bool isLongCastle() const;
    bool isShortCastle() const;
    bool isCapture() const;
    bool isCheck() const;
    bool isCheckMate() const;
    void bindComment(const CommentText &comment);
    void unbindComment();
    void bindVariation(const MoveList &variation);
    void unbindVariations();
    void setGlyphValue(int val=-1);
    int glyphValue() const;

    char fromSquare() const;
    Square toSquare() const;
    Piece piece() const;
    Piece* promoted() const;

    friend std::ostream& operator << ( std::ostream& os, const pgn::Ply& src);

private:

    struct PlyData *hdata;
};
};

#endif 

