#ifndef FENFORM_H
#define FENFORM_H

#include <string>

#include "chessboard.h"

using namespace std;

class FENForm
{
public:
    FENForm();

    string getFENForm(const ChessBoard& chessBoard, PieceColor color);
//    void fromFENForm(const string& fen, ChessBoard& ChessBoard, PieceColor* color);
};

#endif // FENFORM_H
