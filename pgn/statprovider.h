#ifndef STATPROVIDER_H
#define STATPROVIDER_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "positionstat.h"
#include "chessboard.h"

class StatProvider
{
private:
    int getCountOf(const QString& fen, const QString& result);

public:
    StatProvider();

    PositionStat getStatForPosition(ChessBoard& chessBoard, PieceColor color);
};

#endif // STATPROVIDER_H
