#include "statprovider.h"

#include <QString>

#include <iostream>

#include "fenform.h"

int StatProvider::getCountOf(const QString& fen, const QString& result)
{
    QString pattern = "select count(*) as cnt from games where id in (select game_id from moves where "
            "fen like '%1') and result='%2'";
    pattern = pattern.arg(fen).arg(result);

    QSqlQuery query(pattern);
    int cntIdx = query.record().indexOf("cnt");
    std::cout << "cntIdx: " << cntIdx << std::endl;

    while(query.next())
    {
        int count = query.value(cntIdx).toInt();
        std::cout << "cnt: " << count << std::endl;
        return count;
    }

    return -1;
}

StatProvider::StatProvider()
{
}

PositionStat StatProvider::getStatForPosition(ChessBoard& chessBoard, PieceColor color)
{
    FENForm fen;
    QString fenStr = fen.getFENForm(chessBoard, color).c_str();

    int whiteWinsCount = getCountOf(fenStr, "1-0");
    int blackWinsCount = getCountOf(fenStr, "0-1");
    int drawnsCount = getCountOf(fenStr, "1/2-1/2");

    return PositionStat(whiteWinsCount, blackWinsCount, drawnsCount);
}
