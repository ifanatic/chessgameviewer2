#include "fenform.h"

#include <sstream>

#include <vector>


#include "utils.h"

FENForm::FENForm()
{


}

string FENForm::getFENForm(const ChessBoard &chessBoard, PieceColor color)
{
    int freeFieldsCount = 0;

    ChessBoardPiece piece;

    char c = ' ';

    std::ostringstream fenStr;

    for (int i = 7; i >= 0; --i)
    {
        for (int j = 0; j < 8; ++j)
        {
            piece = chessBoard.getPiece(i, j);
            if (piece.type != None)
            {
                if (freeFieldsCount > 0)
                {
                    fenStr << freeFieldsCount;
                }

                c = convertTypeToChar(piece.type);
                if(piece.color == Black)
                {
                    c = tolower(c);
                }
                else
                {
                    c = toupper(c);
                }

                if(c != ' ')
                {
                    fenStr << c;
                }

                freeFieldsCount = 0;
            }
            else
            {
                ++freeFieldsCount;
            }
        }

        if (freeFieldsCount > 0)
        {
            fenStr << freeFieldsCount;
        }

        if (i != 0)
        {
            fenStr << "/";
        }

        freeFieldsCount = 0;
    }

    fenStr << ((color == White) ? " w" : " b");

    fenStr << " ";
    if(chessBoard.isWhiteShortCastleAvaible())
    {
        fenStr << "K";
    }
    if(chessBoard.isWhiteLongCastleAvaible())
    {
        fenStr << "Q";
    }
    if(chessBoard.isBlackShortCastleAvaible())
    {
        fenStr << "k";
    }
    if(chessBoard.isBlackLongCastleAvaible())
    {
        fenStr << "q";
    }

    if(!chessBoard.isLastEnPassant())
    {
        fenStr << " -";
    }

    return fenStr.str();
}


//void FENForm::fromFENForm(const string& fen, ChessBoard& chessBoard, PieceColor* color)
//{
//    chessBoard.clear();

//    char c = '\0';

//    int row = 7;
//    int col = 0;

//    size_t i = 0;

//    std::vector<std::string> rows;

//    std::string currentRow;

//    PieceColor cl = White;

//    while(i < fen.size())
//    {
//        c = fen[i];

//        if(c == '/' || c == ' ')
//        {
//            rows.push_back(currentRow);
//            currentRow.clear();

//            if(c == ' ')
//            {
//                cl = (fen[i + 1] == 'w') ? White : Black;
//                break;
//            }

//            ++i;
//            continue;
//        }

//        currentRow += c;
//        ++i;
//    }

//    if(currentRow.size() != 0)
//    {
//        rows.push_back(currentRow);
//    }



//    std::cout << "sz: " << rows.size() << endl;

//    for(int p = 0; p < 8; ++p)
//    {
//        cout << "\"" << rows[p] << "\"" ;

//        int currentEmptyCount = 0;

//        cout << " rs: " << rows[p].size() << endl;

//        for(int j = 0; j < rows[p].size(); ++j)
//        {
//            c = rows[p][j];

//            if((c >= '1') && (c <= '9'))
//            {
//                for(int k = 0; k < (int)c; ++k, ++j)
//                {
//                    ChessBoardPiece piece;
//                    piece.color = White;
//                    piece.type = None;
//                    chessBoard.setPiece(p, j, piece);
//                }
//            }
//            else if((c >= 'a') && (c <= 'z'))
//            {
//                if(c != 'p')
//                {
//                    c = toupper(c);
//                }

//                ChessBoardPiece piece;
//                piece.color = White;
//                piece.type = convertCharToType(c);

//                chessBoard.setPiece(p, j, piece);
//            }
//            else if((c >= 'A') && (c <= 'Z'))
//            {
//                if(c == 'P')
//                {
//                    c = tolower(c);
//                }

//                ChessBoardPiece piece;
//                piece.color = Black;
//                piece.type = convertCharToType(c);

//                chessBoard.setPiece(p, j, piece);
//            }
//        }
//    }
//}
