#include "gamegateway.h"

#include <vector>
#include <sstream>
#include <iostream>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>

#include "movelist.h"
#include "move.h"
#include "chessboard.h"
#include "fenform.h"

GameGateway::GameGateway()
{
}

bool GameGateway::insertGame(const pgn::Game& game)
{
//    bool isError = false;
    std::vector<MoveData> moves;

    std::ostringstream notationStr;
    std::ostringstream fenStr;

    MoveData moveData;

    FENForm fenForm;

    try
    {
        ChessBoard chessBoard;

        pgn::MoveList::iterator iter = game.moves().begin();
        pgn::MoveList::iterator iterEnd = game.moves().end();

        int moveNumber = 0;

        while(iter != iterEnd)
        {
            notationStr.str("");
            notationStr.clear();
            notationStr << (*iter->white());

            moveData.notation = notationStr.str().c_str();
            moveData.fen = fenForm.getFENForm(chessBoard, White).c_str();
            moveData.moveNumber = moveNumber++;

            moves.push_back(moveData);

            chessBoard.makeMove(White, (*iter->white()));

            notationStr.str("");
            notationStr.clear();

            if(iter->black() == NULL)
            {
                break;
            }

            notationStr << (*iter->black());

            moveData.notation = notationStr.str().c_str();
            moveData.fen = fenForm.getFENForm(chessBoard, Black).c_str();
            moveData.moveNumber = moveNumber++;

            moves.push_back(moveData);

            chessBoard.makeMove(Black, (*iter->black()));

            ++iter;
        }
    }
    catch(MoveException& ex)
    {
        return false;
    }

    QSqlQuery query;
    if(query.prepare("INSERT INTO games(event, site, date, round, white, black, result, eco) "
                     "VALUES(?, ?, ?, ?, ?, ?, ?, ?)"))
    {
        query.bindValue(0/*":event"*/, QVariant(QString(game.tags()["Event"].value().c_str())));
        query.bindValue(1/*":site"*/, QVariant(QString(game.tags()["Site"].value().c_str())));
        query.bindValue(2/*":date"*/, QVariant(QString(game.tags()["Date"].value().c_str())));
        query.bindValue(3/*":round"*/, QVariant(QString(game.tags()["Round"].value().c_str())));
        query.bindValue(4/*":white"*/, QVariant(QString(game.tags()["White"].value().c_str())));
        query.bindValue(5/*":black"*/, QVariant(QString(game.tags()["Black"].value().c_str())));
        query.bindValue(6/*":result"*/, QVariant(QString(game.tags()["Result"].value().c_str())));
        query.bindValue(7/*":eco"*/, QVariant(QString(game.tags()["ECO"].value().c_str())));

        if(!query.exec())
        {
            return false;
            std::cerr << "ERROR:" << query.lastError().driverText().toStdString() << std::endl;
        }
        else
        {
            int gameId = -1;

            if(!query.exec("SELECT max(id) as mid FROM games"))
            {
                cerr << "ERROR: ID" << query.lastError().driverText().toStdString() << endl;
            }
            else
            {
                QSqlRecord rec = query.record();
                int idCol = rec.indexOf("mid");

                while (query.next())
                {
                    gameId = query.value(idCol).toInt();
                    break;
                }
            }

            for(size_t mi = 0; mi < moves.size(); ++mi)
            {
                query.prepare("INSERT INTO moves(game_id, notation, move_number, fen) "
                              "VALUES(?, ?, ?, ?)");
                query.bindValue(0, QVariant(gameId));
                query.bindValue(1, QVariant(moves[mi].notation));
                query.bindValue(2, QVariant(moves[mi].moveNumber));
                query.bindValue(3, QVariant(moves[mi].fen));


                if(!query.exec())
                {
                    cerr << "ERROR: move insert" <<
                            query.lastError().driverText().toStdString() << endl;
                }
            }
        }
    }

    return true;
}
