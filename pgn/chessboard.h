#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <stdexcept>
#include <string>

#include <QString>
#include "ply.h"

enum PieceType
{
    None = 0,
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6
};

enum PieceColor
{
    White = 0,
    Black = 1
};

using namespace pgn;

class ChessBoardPiece {
public:
    PieceType type;
    PieceColor color;

    ChessBoardPiece()
    {
        type = None;
        color = White;
    }

    ChessBoardPiece(PieceType type_, PieceColor color_)
    {
        type = type_;
        color = color_;
    }
};

struct ChessPosition {
    int row;
    int col;

    ChessPosition()
    {
        row = -1;
        col = -1;
    }

    ChessPosition(int row_, int col_)
    {
        row = row_;
        col = col_;
    }
};

class MoveException : public std::runtime_error {
public:
    MoveException(const std::string& message = "") :
        std::runtime_error(message) { }
};

class ChessBoard {
private:
    ChessBoardPiece _gameBoard[8][8];
    QString _fen;

    bool _lastEnPassant;
    ChessPosition _lastSrc;
    ChessPosition _lastDst;

    bool _blackLongCastleMove;
    bool _whiteLongCastleMove;

    bool _blackShortCastleMove;
    bool _whiteShortCastleMove;

    void makeLongCastleMove(PieceColor color);
    void makeShortCastleMove(PieceColor color);

    ChessPosition findBestPieceToMove(PieceColor color, char pieceId,
                                      int rowIndex, int colIndex,
                                      char fromSquare);
    ChessPosition findBestPieceToMove(PieceColor color, const Ply& ply);

public:
    ChessBoard();

    bool isEmpty(int row, int col) const { return _gameBoard[row][col].type == None; }
    PieceColor getColor(int row, int col) const { return _gameBoard[row][col].color; }
    ChessBoardPiece getPiece(int row, int col) const { return _gameBoard[row][col]; }

    void setPiece(int row, int col, const ChessBoardPiece& piece)
        { _gameBoard[row][col] = piece; }

    void makeMove(PieceColor color, const pgn::Ply& ply);

    void init();
    void clear();

    friend std::ostream& operator << (std::ostream& out, const ChessBoard& chessBoard);

    ChessPosition lastSrc() const { return _lastSrc; }
    ChessPosition lastDst() const { return _lastDst; }

    bool isBlackLongCastleAvaible() const { return !_blackLongCastleMove; }
    bool isWhiteLongCastleAvaible() const { return !_whiteLongCastleMove; }
    bool isBlackShortCastleAvaible() const { return !_blackShortCastleMove; }
    bool isWhiteShortCastleAvaible() const { return !_whiteShortCastleMove; }

    bool isLastEnPassant() const { return _lastEnPassant; }

    ChessBoard* clone();
};

#endif  // CHESSBOARD_H
