#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

#include "commenttext.h"
#include "game.h"
#include "gamevollection.h"
#include "gameresult.h"
#include "move.h"
#include "movelist.h"
#include "piece.h"
#include "ply.h"
#include "square.h"
#include "tag.h"
#include "taglist.h"
#include "parser.h"
#include "exception.h"

void pgn::Parser::skipBlanks(std::string::const_iterator &itr1, const std::string::const_iterator &end)
{
    while ((itr1 != end) && (isspace(*itr1)))
    {
        itr1++;
    }
}

bool pgn::Parser::getGameCollection(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::GameCollection &out)
{
    std::string::const_iterator local_itr = itr1;

    pgn::Game *game;

    while ((game = getGame(local_itr, itr2)))
    {
        itr1 = local_itr;
        out.insert(*game);
        delete game;
        gameCount_++;
    }

    return true;
}

pgn::Game* pgn::Parser::getGame(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
    std::string::const_iterator start_game_itr = itr1;
    std::string::const_iterator local_itr = itr1;

    try
    {
        pgn::TagList taglist;
        if (!getTagList(local_itr, itr2, taglist))
            return 0;

        itr1 = local_itr;

        skipBlanks(local_itr, itr2);
        pgn::CommentText bgComment;
        bool hasBgComment = false;
        if (getComment(local_itr, itr2, bgComment))
        {
            hasBgComment = true;
            itr1 = local_itr;
        }

        skipBlanks(local_itr, itr2);
        pgn::MoveList  movelist;
        if (!getMoveList(local_itr, itr2, movelist))
            throw std::runtime_error("Error parsing movelist");

        itr1 = local_itr;

        pgn::GameResult gameResult;
        if (!getGameResult(local_itr, itr2, gameResult))
            return 0;

        itr1 = local_itr;

        pgn::Game *g = new pgn::Game(taglist, movelist, gameResult);

        skipBlanks(local_itr, itr2);
        pgn::CommentText agComment;
        bool hasAgComment = false;
        if (getComment(local_itr, itr2, agComment))
        {
            hasAgComment = true;
            itr1 = local_itr;
        }

        if (hasBgComment) g->bindBeforeGameComment(bgComment);
        if (hasAgComment) g->bindAfterGameComment(agComment);
        return g;
    }
    catch (pgn::ParseException &pe)
    {
        pe.bindParsingText(std::string(start_game_itr, local_itr));
        throw;
    }
    catch (std::exception &e)
    {
        std::ostringstream err;
        err << e.what() << ". I was parsing this game:" << std::string(start_game_itr, local_itr);
        throw std::runtime_error(err.str());
    }
    return 0;
}

bool pgn::Parser::getTagList(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::TagList &out)
{
    std::string::const_iterator local_itr = itr1;

    pgn::TagList taglist;
    pgn::Tag tag;
    while (getTag(local_itr, itr2, tag))
    {
        itr1 = local_itr;
        taglist.insert(tag);
    }
    if (taglist.size() == 0)
        return false;

    out = taglist;
    return true;
}

bool pgn::Parser::getTag(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::Tag &out)
{
    std::string::const_iterator local_itr = itr1;
    std::string::const_iterator start_tag = itr1;

    skipBlanks(local_itr, itr2);
    if (*local_itr != '[')
    {
        return false;
    }
    local_itr++;

    skipBlanks(local_itr, itr2);
    std::string tagname;

    while ((local_itr != itr2) && (isalnum(*local_itr)))
    {
        tagname += *local_itr++;
    }
    itr1 = local_itr;

    skipBlanks(local_itr, itr2);
    std::string tagvalue;

    if (*local_itr != '"')
    {
        pgn::InvalidTag e("1");
        e.bindParsingText(std::string(start_tag, local_itr));
        throw e;
    }
    local_itr++;

    std::string::const_iterator prevIter = local_itr;

    while ((local_itr != itr2) && (*local_itr != ']'))
    {
        prevIter = local_itr;
        tagvalue += (*prevIter);
        ++local_itr;
    }

    if (*local_itr != ']' && (*prevIter != '"'))
    {
        pgn::InvalidTag e("2");
        e.bindParsingText(std::string(start_tag, local_itr));
        throw e;
    }

    tagvalue.erase(tagvalue.begin() + tagvalue.size() - 1);

    local_itr++;
    out = pgn::Tag(tagname, tagvalue);
    itr1 = local_itr;
    return true;
}

bool pgn::Parser::getMoveList(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::MoveList &out)
{
    std::string::const_iterator local_itr = itr1;

    pgn::MoveList ml;

    pgn::CommentText comment;
    if (getComment(local_itr, itr2, comment))
    {
        skipBlanks(local_itr, itr2);
        itr1 = local_itr;
        ml.bindComment(comment);
    }

    skipBlanks(local_itr, itr2);
    pgn::Move *move;
    while ((move = getMove(local_itr, itr2)))
    {
        itr1 = local_itr;
        ml.insert(*move);
        delete move;
    }
    itr1 = local_itr;
    out = ml;

    return true;
}

pgn::Move* pgn::Parser::getMove(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
    std::string::const_iterator local_itr = itr1;
    std::string movenumber;
    int dotsCount;
    if (! getMoveNumber(local_itr, itr2, movenumber, dotsCount))
        return 0;
    itr1 = local_itr;

    skipBlanks(local_itr, itr2);
    pgn::Ply *firstPly=0;
    if ((firstPly = getPly(local_itr, itr2)) == 0)
        throw std::runtime_error("Error parsing move");

    skipBlanks(local_itr, itr2);

    pgn::Ply *secondPly=0;

    if (*local_itr > '9' && *local_itr != '[')
    {
        secondPly = getPly(local_itr, itr2);
        skipBlanks(local_itr, itr2);
    }
    itr1 = local_itr;

    pgn::Move *m = new pgn::Move(firstPly, secondPly, atoi(movenumber.c_str()));

    delete firstPly;
    delete secondPly;
    moveCount_++;
    return m;
}

bool pgn::Parser::getGameResult(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::GameResult &out)
{
    std::string::const_iterator local_itr = itr1;

    std::string result;
    while (!isspace(*local_itr) && local_itr != itr2)
    {
        result += *local_itr++;
    }

    if (result[0] == '[')
    {
        throw pgn::MissingResult();
    }
    else if ( (result != "1-0") &&
              (result != "0-1") &&
              (result != "1/2-1/2") &&
              (result != "*"))
    {
        std::cout << result << std::endl;
        throw pgn::InvalidResult();
    }

    out = result;
    itr1 = local_itr;
    return true;
}

bool pgn::Parser::getMoveNumber(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, std::string &out, int &dotsCount)
{
    std::string::const_iterator local_itr = itr1;

    if (!isdigit(*local_itr))
        return false;


    std::string movenumber;
    while (isdigit(*local_itr) && local_itr != itr2)
    {
        movenumber += *local_itr++;
    }
    skipBlanks(local_itr, itr2);

    if (*local_itr != '.')
    {

        return false;
    }

    dotsCount=0;
    while ((*local_itr == '.') && (local_itr != itr2))
    {
        local_itr++;
        dotsCount++;
    }
    itr1 = local_itr;
    out = movenumber;
    return true;
}

pgn::Ply* pgn::Parser::getPly(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
    std::string::const_iterator local_itr = itr1;

    skipBlanks(local_itr, itr2);
    while (!isspace(*local_itr))
    {
        if (*local_itr != ')')
            local_itr++;
        else
            break;
    }
    pgn::Ply *p = new pgn::Ply(std::string(itr1, local_itr));

    skipBlanks(local_itr, itr2);
    itr1 = local_itr;

    int glyphval = getGlyph(local_itr, itr2);
    if (glyphval >= 0)
    {
        skipBlanks(local_itr, itr2);
        itr1 = local_itr;
        p->setGlyphValue(glyphval);
    }

    itr1 = local_itr;

    pgn::CommentText comment;
    if (getComment(local_itr, itr2, comment))
    {
        skipBlanks(local_itr, itr2);
        itr1 = local_itr;
        p->bindComment(comment);
    }

    itr1 = local_itr;

#if 0
    pgn::MoveList variation;
    if (getVariation(local_itr, itr2, variation))
    {
        skipBlanks(local_itr, itr2);
        itr1 = local_itr;
        p->bindVariation(variation);
    }
#endif
#if 1
    pgn::MoveList variation;
    while (getVariation(local_itr, itr2, variation))
    {
        skipBlanks(local_itr, itr2);
        itr1 = local_itr;
        p->bindVariation(variation);
    }
#endif

    itr1 = local_itr;

    plyCount_++;
    return p;
}

bool pgn::Parser::getComment(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::CommentText &out)
{
    std::string::const_iterator local_itr = itr1;
    std::string comment;
    if (*local_itr != '{')
        return false;
    local_itr++; // skipping '{'

    while ((*local_itr != '}') && (local_itr != itr2))
    {
        comment += *local_itr++;
    }
    local_itr++; // skipping '}'
    skipBlanks(local_itr, itr2);
    itr1 = local_itr;
    out = pgn::CommentText(comment);
    return true;
}

bool pgn::Parser::getVariation(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::MoveList &out)
{
    std::string::const_iterator local_itr = itr1;
    if (*local_itr != '(')
        return false;
    local_itr++; // skipping '('

    if (!getMoveList(local_itr, itr2, out))
        throw std::runtime_error("Error parsing movelist");

    local_itr++; // skipping ')'
    skipBlanks(local_itr, itr2);
    itr1 = local_itr;

    return true;
}

#if 1
void pgn::Parser::checkForVariations(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
    if (*itr1 == '(')
        throw UnsopportedVariations();
}
#endif

int pgn::Parser::getGlyph(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
    if (*itr1 == '$')
    {
        int val = -1;
        itr1++;
        if (isdigit(*itr1))
            val = *itr1 - '0';
        itr1++;
        if (isdigit(*itr1))
            val = val*10 + (*itr1 - '0');
        return val;
    }
    else
        return -1;
}

