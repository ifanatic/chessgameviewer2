#include "chessdbconnection.h"

#include <QSqlDatabase>
#include <QSqlQuery>

bool ChessDbConnection::_isOpened = false;

bool ChessDbConnection::open(const QString& password)
{
    if(_isOpened)
    {
        return true;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./chess.sqlite");
    db.setUserName("chess");
    db.setPassword(password);

    bool ok = db.open();

    if(ok)
    {
        QSqlQuery query(" CREATE TABLE IF NOT EXISTS games(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "event VARCHAR(250), site VARCHAR(250), round VARCHAR(250), date VARCHAR(250), "
                        "white VARCHAR(250), black VARCHAR(250), result VARCHAR(250), ECO VARCHAR(250))");

        query.exec();

        query.exec("CREATE TABLE IF NOT EXISTS moves(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "game_id INTEGER, notation VARCHAR(250), move_number INTEGER, fen VARCHAR(250), "
                       "FOREIGN KEY(game_id) REFERENCES games(id)"
                       ")");
        _isOpened = true;
    }
    else
    {
        _isOpened = false;
        return false;
    }
}
