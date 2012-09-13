#include "utils.h"

PieceType convertCharToType(char type)
{
    switch(type)
    {
    case 'R':
        return Rook;
    case 'B':
        return Bishop;
    case 'N':
        return Knight;
    case 'Q':
        return Queen;
    case 'K':
        return King;
    case 'p':
        return Pawn;
    }

    return None;
}

char convertTypeToChar(PieceType type)
{
    switch(type)
    {
    case Rook:
        return 'R';
    case Bishop:
        return 'B';
    case Knight:
        return 'N';
    case Queen:
        return 'Q';
    case King:
        return 'K';
    case Pawn:
        return 'P';
    default:
        return ' ';
    }

    return ' ';
}

QString getFileNameForPiece(ChessBoardPiece piece)
{
    if(piece.type == None)
    {
        return "";
    }

    if(piece.color == Black)
    {
        switch(piece.type)
        {
        case Pawn:
            return ":/Images/blackPawn.bmp";
        case Knight:
            return ":/Images/blackKnight.bmp";
        case Bishop:
            return ":/Images/blackBishop.bmp";
        case Rook:
            return ":/Images/blackCastle.bmp";
        case Queen:
            return ":/Images/blackQueen.bmp";
        case King:
            return ":/Images/blackKing.bmp";
        }
    }
    else
    {
        switch(piece.type)
        {
        case Pawn:
            return ":/Images/whitePawn.bmp";
        case Knight:
            return ":/Images/whiteKnight.bmp";
        case Bishop:
            return ":/Images/whiteBishop.bmp";
        case Rook:
            return ":/Images/whiteCastle.bmp";
        case Queen:
            return ":/Images/whiteQueen.bmp";
        case King:
            return ":/Images/whiteKing.bmp";
        }
    }


}
