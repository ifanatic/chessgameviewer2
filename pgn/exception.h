#ifndef PGNException_h
#define PGNException_h

#include <exception>
#include <string>

namespace pgn
{
class ParseException : public std::exception
{
public:
    
    ParseException(const std::string &message) throw():message_(message) {}
    ~ParseException() throw() {}
    void bindParsingText(const std::string &parsingtext) throw() { parsing_text_ = parsingtext; }
    const char *parsing_text() const throw() { return parsing_text_.c_str(); }
    virtual const char *what() const throw() { return message_.c_str(); }

private:

    std::string message_;
    std::string parsing_text_;
};

class InvalidCastleString : public ParseException
{
public:
    
    InvalidCastleString() throw();
    ~InvalidCastleString() throw() {};
};

class InvalidPlyText : public ParseException
{
public:
    
    ~InvalidPlyText() throw() {};
    InvalidPlyText(const std::string &ply) throw();
};

class InvalidTag : public ParseException
{
private:
    std::string _tag;

public:
    
    ~InvalidTag() throw() {};
    InvalidTag(const std::string& tag = "") throw();

    std::string getTag() const { return _tag; }
};

class InvalidResult : public ParseException
{
public:
    
    ~InvalidResult() throw() {};
    InvalidResult() throw();
};

class MissingResult : public ParseException
{
public:
    
    ~MissingResult() throw() {};
    MissingResult() throw();
};


class UnsopportedVariations : public ParseException
{
public:
    
    ~UnsopportedVariations() throw() {};
    UnsopportedVariations() throw();
};


class UnsaportedGlyphs : public ParseException
{
public:
    
    ~UnsaportedGlyphs() throw() {};
    UnsaportedGlyphs() throw();
};

}


#endif 

