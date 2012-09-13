#include "chessboard.h"

#include <cstdio>
#include <ctype.h>
#include <iostream>

#include "ply.h"
#include "movecheckersrepository.h"
#include "utils.h"

using namespace pgn;

void ChessBoard::makeLongCastleMove(PieceColor color)
{
    if(color == White)
    {
        _whiteLongCastleMove = true;
    }
    else
    {
        _blackLongCastleMove = true;
    }

    int row = (color == White) ? 0 : 7;

    _gameBoard[row][0].color = White;
    _gameBoard[row][0].type = None;
    _gameBoard[row][4].color = White;
    _gameBoard[row][4].type = None;

    _gameBoard[row][2].type = King;
    _gameBoard[row][2].color = color;
    _gameBoard[row][3].type = Rook;
    _gameBoard[row][3].color = color;

    _lastSrc = ChessPosition(row, 4);
    _lastDst = ChessPosition(row, 2);
}

void ChessBoard::makeShortCastleMove(PieceColor color)
{
    if(color == White)
    {
        _whiteShortCastleMove = true;
    }
    else
    {
        _blackShortCastleMove = true;
    }

    int row = (color == White) ? 0 : 7;

    _gameBoard[row][7].color = White;
    _gameBoard[row][7].type = None;
    _gameBoard[row][4].color = White;
    _gameBoard[row][4].type = None;

    _gameBoard[row][6].type = King;
    _gameBoard[row][6].color = color;
    _gameBoard[row][5].type = Rook;
    _gameBoard[row][5].color = color;

    _lastSrc = ChessPosition(row, 4);
    _lastDst = ChessPosition(row, 6);
}


ChessPosition ChessBoard::findBestPieceToMove(PieceColor color, char pieceId,
                                              int rowIndex, int colIndex,
                                              char fromSquare)
{
    PieceType type = convertCharToType(pieceId);

    int srcRow = -1;
    int srcCol = -1;

    BasicMoveChecker* movingChecker = MoveCheckersRepository::instance()->getCheckerByType(type);

    if(movingChecker == NULL)
    {
        std::cerr << "Moving Checker is NULL" << std::endl;
        return ChessPosition(-1, -1);
    }

    //    std::cout << "Ply: " << ply.toSquare().rowIndex() << ", " << ply.toSquare().colIndex() << std::endl;

    bool bestFound = false;

    // find src
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            if(_gameBoard[i][j].type != type)
            {
                continue;
            }

            if(_gameBoard[i][j].color != color)
            {
                continue;
            }

            if(movingChecker->canMoveTo(i, j, color,
                                        rowIndex,
                                        colIndex,
                                        (*this)))
            {
                //                std::cout << "Can move!" << std::endl;

                if(fromSquare == '-')
                {
                    srcRow = i;
                    srcCol = j;
                    bestFound = true;
                    break;
                }
                else
                {
                    //                    std::cout << "ply.fromSquare: " << ply.fromSquare() << std::endl;
                    //                    std::cout << "i: " << i << ", j: " << j << std::endl;

                    if(isRow(fromSquare))
                    {
                        //                        std::cout << "isRow true" << std::endl;

                        if(i == (fromSquare - '1'))
                        {
                            srcRow = i;
                            srcCol = j;
                            bestFound = true;
                            break;
                        }
                    }
                    else
                    {
                        //                        std::cout << "isCol true" << std::endl;
                        if(j == (fromSquare - 'a'))
                        {
                            srcRow = i;
                            srcCol = j;
                            bestFound = true;
                            break;
                        }
                    }
                }
            }
        }

        if(bestFound)
        {
            break;
        }
    }

    return ChessPosition(srcRow, srcCol);
}

ChessPosition ChessBoard::findBestPieceToMove(PieceColor color, const Ply& ply)
{
    return findBestPieceToMove(color, ply.piece().id(), ply.toSquare().rowIndex(),
                               ply.toSquare().colIndex(), ply.fromSquare());
}

void ChessBoard::init()
{
    for(int i = 2; i < 6; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            _gameBoard[i][j] = ChessBoardPiece(None, White);
        }
    }


    // set white pieces
    _gameBoard[0][0] = ChessBoardPiece(Rook,      White);
    _gameBoard[0][1] = ChessBoardPiece(Knight,    White);
    _gameBoard[0][2] = ChessBoardPiece(Bishop,    White);
    _gameBoard[0][3] = ChessBoardPiece(Queen,     White);
    _gameBoard[0][4] = ChessBoardPiece(King,      White);
    _gameBoard[0][5] = ChessBoardPiece(Bishop,    White);
    _gameBoard[0][6] = ChessBoardPiece(Knight,    White);
    _gameBoard[0][7] = ChessBoardPiece(Rook,      White);

    _gameBoard[7][0] = ChessBoardPiece(Rook,      Black);
    _gameBoard[7][1] = ChessBoardPiece(Knight,    Black);
    _gameBoard[7][2] = ChessBoardPiece(Bishop,    Black);
    _gameBoard[7][3] = ChessBoardPiece(Queen,     Black);
    _gameBoard[7][4] = ChessBoardPiece(King,      Black);
    _gameBoard[7][5] = ChessBoardPiece(Bishop,    Black);
    _gameBoard[7][6] = ChessBoardPiece(Knight,    Black);
    _gameBoard[7][7] = ChessBoardPiece(Rook,      Black);

    for(int i = 0; i < 8; ++i)
    {
        _gameBoard[1][i] = ChessBoardPiece(Pawn, White);
        _gameBoard[6][i] = ChessBoardPiece(Pawn, Black);
    }

    _lastEnPassant = false;

    _whiteLongCastleMove = false;
    _whiteShortCastleMove = false;
    _blackLongCastleMove = false;
    _blackShortCastleMove = false;
}

ChessBoard::ChessBoard()
{
    init();
}

void ChessBoard::clear()
{
    _lastSrc = ChessPosition();
    _lastDst = ChessPosition();

    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            _gameBoard[i][j].color = White;
            _gameBoard[i][j].type = None;
        }
    }
}

void ChessBoard::makeMove(PieceColor color, const pgn::Ply& ply)
{
    if(ply.isLongCastle())
    {
        makeLongCastleMove(color);
        return;
    }

    if(ply.isShortCastle())
    {
        makeShortCastleMove(color);
        return;
    }

    int srcRow = -1;
    int srcCol = -1;
    int dstRow = ply.toSquare().rowIndex();
    int dstCol = ply.toSquare().colIndex();

    ChessPosition bestPos = findBestPieceToMove(color, ply.piece().id(),
                                                ply.toSquare().rowIndex(),
                                                ply.toSquare().colIndex(),
                                                ply.fromSquare());

    srcRow = bestPos.row;
    srcCol = bestPos.col;

    if(ply.piece() == pgn::Piece::Pawn())
    {
        if(!ply.isCapture())
        {
            if((srcRow == 6) && (ply.toSquare().rowIndex() == 4))
            {
                _lastEnPassant = true;
            }
            else if((srcRow == 1) && (ply.toSquare().rowIndex() == 3))
            {
                _lastEnPassant = true;
            }
            else
            {
                _lastEnPassant = false;
            }
        }
        else
        {
            if(_lastEnPassant && isEmpty(dstRow, dstCol))
            {

                if((srcRow == -1) || (srcCol == -1))
                {
                    int direction = (_lastDst.row == 5) ? -1 : 1;
                    if(_lastDst.row == 3)
                    {
                        direction = -1;
                    }

                    _gameBoard[_lastDst.row + direction][_lastDst.col] =
                            _gameBoard[_lastDst.row][_lastDst.col];

                    _gameBoard[_lastDst.row][_lastDst.col].color = White;
                    _gameBoard[_lastDst.row][_lastDst.col].type = None;

                    bestPos = findBestPieceToMove(color, ply);

                    srcRow = bestPos.row;
                    srcCol = bestPos.col;
                }
            }

            _lastEnPassant = false;
        }
    }
    else
    {
        if(srcRow < 0 || srcCol < 0)
        {

            if(dstRow == 7 || dstRow == 0)
            {

                bestPos = findBestPieceToMove(color, pgn::Piece::Pawn().id(), dstRow, dstCol, ply.fromSquare());

                srcRow = bestPos.row;
                srcCol = bestPos.col;
            }
        }

        _lastEnPassant = false;
    }



    if(srcRow < 0 || srcCol < 0)
    {

        throw MoveException();

        return;
    }

    _gameBoard[dstRow][dstCol].type =
            convertCharToType(ply.piece().id());
    _gameBoard[dstRow][dstCol].color = color;

    _gameBoard[srcRow][srcCol].type = None;
    _gameBoard[srcRow][srcCol].color = White;

    _lastSrc = ChessPosition(srcRow, srcCol);
    _lastDst = ChessPosition(dstRow, dstCol);
}

ChessBoard* ChessBoard::clone()
{
    ChessBoard* result = new ChessBoard();
    result->_fen = this->_fen;

    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            result->_gameBoard[i][j] = this->_gameBoard[i][j];
        }
    }

    result->_lastDst = this->_lastDst;
    result->_lastEnPassant = this->_lastEnPassant;
    result->_lastSrc = this->_lastSrc;

    return result;
}

std::ostream& operator << (std::ostream& out, const ChessBoard& chessBoard)
{
    char c = ' ';

    for(int i = 7; i >= 0; --i)
    {
        for(int j = 0; j < 8; ++j)
        {
            c = convertTypeToChar(chessBoard._gameBoard[i][j].type);
            if(chessBoard._gameBoard[i][j].color == Black)
            {
                c = tolower(c);
                if(c == 'p')
                {
                    c = 'l';
                }
            }
            out << c << "";
        }

        out << std::endl;
    }

    return out;
}
