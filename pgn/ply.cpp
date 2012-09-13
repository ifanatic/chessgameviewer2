#include <cstdio>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "ply.h"
#include "commenttext.h"
#include "movelist.h"
#include "exception.h"

#include <iostream>

namespace pgn 
{
const char longCastleFlag  = 0x01;
const char shortCastleFlag = 0x02;
const char captureFlag     = 0x04;
const char checkFlag       = 0x08;
const char checkmateFlag   = 0x10;
struct PlyData
{
    pgn::Piece piece;
    pgn::Piece *promoted;
    char fromSquare;
    pgn::Square toSquare;
    char flags;
    pgn::CommentText *comment;
    std::vector<pgn::MoveList *>variation;
    char glyphval;
};
};

pgn::Ply::Ply(const pgn::Ply& src) 
{
    hdata = new PlyData;

    hdata->piece = src.hdata->piece;
    hdata->fromSquare = src.hdata->fromSquare;
    hdata->toSquare = src.hdata->toSquare;
    hdata->flags = src.hdata->flags;
    hdata->glyphval = src.hdata->glyphval;
    if (src.hdata->promoted)
        hdata->promoted = new pgn::Piece(*(src.hdata->promoted));
    else
        hdata->promoted = 0;
    if (src.hdata->comment)
        hdata->comment = new pgn::CommentText(*(src.hdata->comment));
    else
        hdata->comment = 0;
#if 0
    if (src.hdata->variation)
        hdata->variation = new pgn::MoveList(*(src.hdata->variation));
    else
        hdata->variation = 0;
#endif
    for (unsigned int i=0; i<src.hdata->variation.size(); ++i)
        hdata->variation.push_back(new pgn::MoveList(*(src.hdata->variation[i])));

}

pgn::Ply::Ply(const std::string& ply_text)
{
    hdata = new PlyData;
    hdata->flags = 0;
    hdata->fromSquare = '-';
    hdata->comment = 0;
    hdata->promoted = 0;
    hdata->glyphval = -1;
    std::string ptext = ply_text;

    char piece_char = '-';
    char col_coor = '-';
    char row_coor = '-';
    std::string extra_signs;
    std::string::const_iterator pitr = ptext.begin();
    char promoted_piece = '-';
    for (pitr = ply_text.begin(); pitr != ply_text.end(); pitr++)
    {
        switch (*pitr)
        {
        case 'R':
        case 'K':
        case 'Q':
        case 'B':
        case 'N':
            if (*(pitr-1) == '=')
                promoted_piece = *pitr;
            else
                piece_char = *pitr;
            break;
        case 'x':
            hdata->flags |= captureFlag;
            break;
        case '#':
            hdata->flags |= checkmateFlag;
            break;
        case '+':
            hdata->flags |= checkFlag;
            break;
        case 'O':
        case '-':
        case '=':
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
            if (col_coor == '-')
            {
                col_coor = *pitr;
            }
            else
            {
                hdata->fromSquare = col_coor;
                col_coor = *pitr;
            }
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            if (row_coor == '-')
            {
                row_coor = *pitr;
            }
            else
            {
                hdata->fromSquare = row_coor;
                row_coor = *pitr;
            }
            break;
        case '0':
            throw pgn::InvalidCastleString();
            break;
        default:
        {

            throw pgn::InvalidPlyText(ptext);
        }
            break;
        }
    }
    if (ptext.find("O-O-O") != std::string::npos)
    {
        hdata->flags |= longCastleFlag;
    }
    else if (ptext.find("O-O") != std::string::npos)
    {
        hdata->flags |= shortCastleFlag;
    }
    else
    {
        if (piece_char == '-')
            hdata->piece = pgn::Piece();
        else
            hdata->piece = pgn::Piece(piece_char);
        if (promoted_piece != '-')
            hdata->promoted = new pgn::Piece(promoted_piece);
        hdata->toSquare = pgn::Square(col_coor,row_coor);
    }
}

pgn::Ply::~Ply() 
{
    unbindVariations();
    delete hdata->comment;
    delete hdata->promoted;
    delete hdata;
}

pgn::Ply& pgn::Ply::operator = (const pgn::Ply& src) 
{
    if (&src == this)
        return(*this);

    hdata->piece = src.hdata->piece;
    hdata->fromSquare = src.hdata->fromSquare;
    hdata->toSquare = src.hdata->toSquare;
    hdata->flags = src.hdata->flags;
    hdata->glyphval = src.hdata->glyphval;

    if (src.hdata->promoted)
    {
        delete hdata->promoted;
        hdata->promoted = new pgn::Piece(*(src.hdata->promoted));
    }
    else
        hdata->promoted = 0;

    if (src.hdata->comment)
    {
        delete hdata->comment;
        hdata->comment = new pgn::CommentText(*(src.hdata->comment));
    }
    else
        hdata->comment = 0;
#if 0
    if (src.hdata->variation)
    {
        delete hdata->variation;
        hdata->variation = new pgn::MoveList(*(src.hdata->variation));
    }
    else
        hdata->variation = 0;
#endif
    unbindVariations();
    for (unsigned int i=0; i<src.hdata->variation.size(); ++i)
        hdata->variation.push_back(new pgn::MoveList(*(src.hdata->variation[i])));

    return *this;
}

bool pgn::Ply::operator == (const pgn::Ply& src) const
{
    if (hdata->piece != src.hdata->piece)
        return false;
    if (hdata->fromSquare != src.hdata->fromSquare)
        return false;
    if (hdata->toSquare != src.hdata->toSquare)
        return false;
    if (hdata->flags != src.hdata->flags)
        return false;
    if (hdata->glyphval != src.hdata->glyphval)
        return false;

    if ((hdata->promoted != 0) && (src.hdata->promoted != 0) &&
            *(hdata->promoted) != *(src.hdata->promoted))
        return false;

    if (((hdata->promoted == 0) && (src.hdata->promoted != 0)) ||
            ((hdata->promoted != 0) && (src.hdata->promoted == 0)))
        return false;

    if ((hdata->comment != 0) && (src.hdata->comment != 0) &&
            *(hdata->comment) != *(src.hdata->comment))
        return false;

    if (((hdata->comment == 0) && (src.hdata->comment != 0)) ||
            ((hdata->comment != 0) && (src.hdata->comment == 0)))
        return false;
#if 0
    if ((hdata->variation != 0) && (src.hdata->variation != 0) &&
            *(hdata->variation) != *(src.hdata->variation))
        return false;

    if (((hdata->variation == 0) && (src.hdata->variation != 0)) ||
            ((hdata->variation != 0) && (src.hdata->variation == 0)))
        return false;
#endif

    return true;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::Ply& src ) 
{
    if (src.isLongCastle())
    {
        os << "O-O-O";
        if (src.isCheckMate())
            os << "#";
        else if (src.isCheck())
            os << "+";
    }
    else if (src.isShortCastle())
    {
        os << "O-O";
        if (src.isCheckMate())
            os << "#";
        else if (src.isCheck())
            os << "+";
    }
    else
    {
        os << src.hdata->piece;
        if (src.hdata->fromSquare != '-')
            os << src.hdata->fromSquare;
        if (src.isCapture())
            os << "x";
        os << src.hdata->toSquare.col() << src.hdata->toSquare.row();
        if (src.hdata->promoted)
            os << "=" << *(src.hdata->promoted);
        if (src.isCheckMate())
            os << "#";
        else if (src.isCheck())
            os << "+";
    }

    if (src.hdata->glyphval >= 0)
        os << "$" << src.hdata->glyphval;

    if (src.hdata->comment)
        os << *(src.hdata->comment);

    for (unsigned int i=0; i<src.hdata->variation.size(); ++i)
        os << "(" << *(src.hdata->variation[i]) << ") ";

    return os;
}

bool pgn::Ply::operator != (const pgn::Ply& src) const 
{
    return !(src == *this);
}

bool pgn::Ply::isLongCastle() const 
{ 
    return hdata->flags & longCastleFlag;
}

bool pgn::Ply::isShortCastle() const 
{ 
    return hdata->flags & shortCastleFlag;
}

bool pgn::Ply::isCapture() const 
{ 
    return hdata->flags & captureFlag;
}

bool pgn::Ply::isCheck() const 
{ 
    return hdata->flags & checkFlag;
}

bool pgn::Ply::isCheckMate() const 
{ 
    return hdata->flags & checkmateFlag;
}

char pgn::Ply::fromSquare() const 
{ 
    return hdata->fromSquare;
}

pgn::Square pgn::Ply::toSquare() const 
{ 
    return hdata->toSquare;
}

pgn::Piece pgn::Ply::piece() const 
{ 
    return hdata->piece;
}

pgn::Piece* pgn::Ply::promoted() const 
{ 
    return hdata->promoted;
}

void pgn::Ply::setGlyphValue(int glyphval)
{
    hdata->glyphval = glyphval;
}

int pgn::Ply::glyphValue() const
{
    return hdata->glyphval;
}

void pgn::Ply::bindComment(const CommentText &comment)
{
    delete hdata->comment;
    hdata->comment = new pgn::CommentText(comment);
}

void pgn::Ply::unbindComment()
{
    delete hdata->comment;
    hdata->comment = 0;
}

void pgn::Ply::bindVariation(const MoveList &variation)
{
    hdata->variation.push_back(new pgn::MoveList(variation));
}

void pgn::Ply::unbindVariations()
{
    for (unsigned int i=0; i<hdata->variation.size(); ++i)
        delete hdata->variation[i];
    hdata->variation.clear();
}

