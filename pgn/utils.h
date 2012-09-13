#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "chessboard.h"

PieceType convertCharToType(char type);

char convertTypeToChar(PieceType type);

inline bool isRow(char c)
{
    return (c >= '1') && (c <= '8');
}

QString getFileNameForPiece(ChessBoardPiece piece);


#endif // UTILS_H
