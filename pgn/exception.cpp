#include "exception.h"

pgn::InvalidCastleString::InvalidCastleString() throw()
    :pgn::ParseException("invalid string for castle (maybe 0 (zero) used instead of 'O')")
{
}

pgn::InvalidPlyText::InvalidPlyText(const std::string &ply) throw()
    :pgn::ParseException("invalid text in ply " + ply)
{
}

pgn::InvalidTag::InvalidTag(const std::string& tag) throw()
    :pgn::ParseException("invalid tag"), _tag(tag)
{
}

pgn::InvalidResult::InvalidResult() throw()
    :pgn::ParseException("invalid result")
{
}

pgn::MissingResult::MissingResult() throw()
    :pgn::ParseException("missing result")
{
}

pgn::UnsopportedVariations::UnsopportedVariations() throw()
    :pgn::ParseException("support for variations not yet available in pgnlib")
{
}

pgn::UnsaportedGlyphs::UnsaportedGlyphs() throw()
    :pgn::ParseException("support for glyphs not yet available in pgnlib")
{
}

