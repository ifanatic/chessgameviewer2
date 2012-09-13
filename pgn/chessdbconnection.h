#ifndef CHESSDBCONNECTION_H
#define CHESSDBCONNECTION_H

#include <QString>

class ChessDbConnection
{
private:
    static bool _isOpened;

public:
    static bool open(const QString& password = "chess");
    static bool isOpened() { return _isOpened; }
};

#endif // CHESSDBCONNECTION_H
