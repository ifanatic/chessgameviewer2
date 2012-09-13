#ifndef PGNCommentText_h
#define PGNCommentText_h

#include <fstream>
#include <string>

namespace pgn
{
class CommentText
{
public:

    CommentText();
    CommentText(const std::string &s);
    CommentText(const CommentText& src);

    virtual ~CommentText();

    CommentText& operator = (const CommentText& src);
    bool operator == (const CommentText& src) const;
    bool operator != (const CommentText& src) const;

    friend std::ostream& operator << ( std::ostream& os, const CommentText& src);

private:

    struct CommentTextData *hdata;

};
std::ostream& operator << ( std::ostream& os, const pgn::CommentText& src );
};

#endif 

