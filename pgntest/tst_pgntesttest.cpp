#include <QtCore/QString>
#include <QtTest/QtTest>

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "../pgn/chessboard.h"
#include "../pgn/basicmovechecker.h"
#include "../pgn/bishopmovechecker.h"
#include "../pgn/rookmovechecker.h"
#include "../pgn/ply.h"
#include "../pgn/fenform.h"
#include "../pgn/gameplayer.h"
#include "../pgn/kingmovechecker.h"
#include "../pgn/knightmovechecker.h"
#include "../pgn/pawnmovechecker.h"
#include "../pgn/gameresult.h"
#include "../pgn/parser.h"
#include "../pgn/gamevollection.h"
#include "../pgn/game.h"
#include "../pgn/move.h"
#include "../pgn/taglist.h"
#include "../pgn/tag.h"
#include "../pgn/piecepathtracer.h"
#include "../pgn/ply.h"
#include "../pgn/movelist.h"

const std::string validPgnGame = "[Event \"?\"]"
        "[Site \"corr CS ch xx (FS\"]"
        "[Date \"????.??.??\"]"
        "[Round \"1024\"]"
        "[White \"Pecenka X\"]"
        "[Black \"Nun J\"]"
        "[Result \"1-0\"]"
        "[ECO \"A67/01\"]"
        ""
        "1.d4 Nf6 2.c4 c5 3.d5 e6 4.Nc3 exd5 "
        "5.cxd5 d6 6.e4 g6 7.f4 Bg7 8.Bb5+ Nfd7 "
        "9.a4 Qh4+ 10.g3 Qe7 11.Nf3 O-O 12.O-O Na6 "
        "13.e5 Nb4 14.Ne4 dxe5 15.d6 Qd8 16.fxe5 Nc6 "
        "17.Bg5 Qb6 18.Nf6+ Kh8 19.Nd5 Qa5 20.Nd2 Ndxe5 "
        "21.Nb3 Bg4 22.Qc1 Nf3+ 23.Rxf3 Bxf3 24.Nxa5 Bxd5 "
        "25.Nxc6 bxc6 26.Qxc5  1-0 "
        "\n"
        "\n";

const std::string invalidPgnGame =
        "[Event \"?\"] "
        "[Site \"?\"] "
        "[Date \"2012.05.30\"]"
        "[Round \"?\"]"
        "[White \"White Player\"]"
        "[Black \"Black Player\"]"
        "[Result \"*\"]"
        "[ECO \"C20\"]"
        "[PlyCount \"5\"]"
        ""
        "1. e4 e5 2. Ne2 Nf6 3. Nc9 *"
        "\n";

class PgntestTest : public QObject
{
    Q_OBJECT

public:
    PgntestTest();

private Q_SLOTS:
    void BasicMoveChecker_doNotMoveToBeyond();
    void BasicMoveChecker_goToEmptyCell();
    void BasicMoveChecker_doNotMoveOnFrienCell();

    void BishopMoveChecker_onlyCanMoveOnDiagonal();

    void RookMoveChecker_canMoveOnRowsAndCols();

    void KingMoveChecker_CannotMoveToLongDistance();
    void KingMoveChecker_CanMoveInOneCellDistance();

    void KnightMoveChecker_checkNormalMove();

    void PawnMoveChecker_checkPossibleEnPassante();
    void PawnMoveChecker_canCaptureOnForwardDiagonal();

    void ChessBoard_defaultPosition();
    void ChessBoard_checkColorOnDefaultPos();
    void ChessBoard_checkSimpleMove();
    void ChessBoard_checkFigureMove();

    void FENForm_convertPoseToFen();

    void GameResult_checkAllPossiblesResults();

    void Ply_checkLongCastle();
    void Ply_checkShortCastle();
    void Ply_isCheck();
    void Ply_isCheckAndMate();
    void Ply_checkFromSquare();
    void Ply_checkToSquare();
    void Ply_checkPiece();

    void GamePlayer_checkBeginState();
    void GamePlayer_preformMove();
    void GamePlayer_checkEndState();
    void GamePlayer_ifMoveIsNotExistsReturnFalse();

    void Parser_ParseValidFile();
    void Parser_DoNotParseInvalidFile();
};

PgntestTest::PgntestTest()
{
}

void PgntestTest::BasicMoveChecker_doNotMoveToBeyond()
{
    ChessBoard cb;
    BasicMoveChecker checker;
    QVERIFY(!checker.canMoveTo(0, 5, White, -1, 20, cb));
}


void PgntestTest::BasicMoveChecker_goToEmptyCell()
{
    ChessBoard cb;
    BasicMoveChecker checker;
    QVERIFY(checker.canMoveTo(0, 5, White, 5, 5, cb));
}

void PgntestTest::BasicMoveChecker_doNotMoveOnFrienCell()
{
    ChessBoardPiece piece;
    piece.color = White;
    piece.type = Rook;

    ChessBoard cb;
    cb.setPiece(5, 5, piece);
    BasicMoveChecker checker;
    QVERIFY(!checker.canMoveTo(0, 5, White, 5, 5, cb));
}

void PgntestTest::BishopMoveChecker_onlyCanMoveOnDiagonal()
{
    ChessBoard cb;
    BishopMoveChecker checker;

    QVERIFY(checker.canMoveTo(1, 1, White, 5, 5, cb));
    QVERIFY(checker.canMoveTo(3, 4, White, 2, 3, cb));

    QVERIFY(!checker.canMoveTo(1, 1, White, 5, 6, cb));
}

void PgntestTest::RookMoveChecker_canMoveOnRowsAndCols()
{
    ChessBoard cb;
    RookMoveChecker checker;

    QVERIFY(!checker.canMoveTo(1, 1, White, 5, 5, cb));
    QVERIFY(checker.canMoveTo(3, 4, White, 3, 5, cb));
}

void PgntestTest::KingMoveChecker_CannotMoveToLongDistance()
{
    ChessBoard cb;

    KingMoveChecker checker;

    QVERIFY(!checker.canMoveTo(3, 4, Black, 5, 6, cb));
}

void PgntestTest::KingMoveChecker_CanMoveInOneCellDistance()
{
    ChessBoard cb;

    KingMoveChecker checker;

    QVERIFY(checker.canMoveTo(4, 4, Black, 3, 3, cb));
}

void PgntestTest::KnightMoveChecker_checkNormalMove()
{
    ChessBoard cb;

    KingMoveChecker checker;

    QVERIFY(!checker.canMoveTo(0, 0, Black, 1, 2, cb));
}


void PgntestTest::PawnMoveChecker_checkPossibleEnPassante()
{
    ChessBoard cb;
    cb.clear();


    PawnMoveChecker checker;

    QVERIFY(checker.canMoveTo(1, 0, White, 3, 0, cb));
}

void PgntestTest::PawnMoveChecker_canCaptureOnForwardDiagonal()
{
    ChessBoard cb;
    ChessBoardPiece piece;
    piece.color = Black;
    piece.type = Pawn;

    cb.setPiece(2, 1, piece);

    PawnMoveChecker checker;

    QVERIFY(checker.canMoveTo(1, 0, White, 2, 1, cb));
}


void PgntestTest::ChessBoard_defaultPosition()
{
    ChessBoard cb;
    QCOMPARE((int)cb.getPiece(0, 0).type, (int)Rook);
    QCOMPARE((int)cb.getPiece(1, 1).type, (int)Pawn);
}

void PgntestTest::ChessBoard_checkColorOnDefaultPos()
{
    ChessBoard cb;
    QCOMPARE((int)cb.getPiece(1, 6).color, (int)White);
    QCOMPARE((int)cb.getPiece(7, 6).color, (int)Black);
}

void PgntestTest::ChessBoard_checkSimpleMove()
{
    ChessBoard cb;
    pgn::Ply ply("e4");
    cb.makeMove(White, ply);
    QCOMPARE((int)cb.getPiece(3, 4).type, (int)Pawn);
}

void PgntestTest::ChessBoard_checkFigureMove()
{
    ChessBoard cb;
    pgn::Ply ply("Nf3");
    cb.makeMove(White, ply);
    QCOMPARE((int)cb.getPiece(2, 5).type, (int)Knight);
}

void PgntestTest::FENForm_convertPoseToFen()
{
    ChessBoardPiece piece;
    piece.color = White;
    piece.type = None;
    ChessBoard cb;
    cb.setPiece(1, 4, piece);
    piece.color = White;
    piece.type = Pawn;
    cb.setPiece(3, 4, piece);

    FENForm fenForm;
    QString fenStr = fenForm.getFENForm(cb, White).c_str();

    QCOMPARE(fenStr, QString("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq -"));
}

void PgntestTest::GameResult_checkAllPossiblesResults()
{
    GameResult whiteWin("1-0");
    QVERIFY(whiteWin.isWhiteWin());

    GameResult blackWin("0-1");
    QVERIFY(blackWin.isBlackWin());

    GameResult drawn("1/2-1/2");
    QVERIFY(drawn.isDrawn());

    GameResult unknown("*");
    QVERIFY(unknown.isUnknown());
}

void PgntestTest::Ply_checkLongCastle()
{
    pgn::Ply ply("O-O-O");
    QVERIFY(ply.isLongCastle());
}

void PgntestTest::Ply_checkShortCastle()
{
    pgn::Ply ply("O-O");
    QVERIFY(ply.isShortCastle());
}

void PgntestTest::Ply_isCheck()
{
    pgn::Ply ply("e5+");
    QVERIFY(ply.isCheck());
}

void PgntestTest::Ply_isCheckAndMate()
{
    pgn::Ply ply("e5#");
    QVERIFY(ply.isCheckMate());
}

void PgntestTest::Ply_checkFromSquare()
{
    pgn::Ply ply("cd4");
    QCOMPARE(ply.fromSquare(), 'c');
}

void PgntestTest::Ply_checkToSquare()
{
    pgn::Ply ply("cd4");
    QCOMPARE(ply.toSquare().row(), '4');
    QCOMPARE(ply.toSquare().col(), 'd');
}

void PgntestTest::Ply_checkPiece()
{
    pgn::Ply ply("Rcd4");
    QCOMPARE(ply.piece().id(), 'R');
}

void PgntestTest::GamePlayer_checkBeginState()
{
    GamePlayer player;
    player.goToBegin();

    QCOMPARE((int)player.currentColor(), (int)White);
}


void PgntestTest::GamePlayer_preformMove()
{
    vector<pgn::Ply> moves;
    moves.push_back(pgn::Ply("e4"));
    moves.push_back(pgn::Ply("e5"));

    GamePlayer player;
    player.setMoves(moves);
    player.goToBegin();
    player.next();

    QCOMPARE((int)player.chessBoard().getPiece(3, 4).type, (int)Pawn);
}

void PgntestTest::GamePlayer_checkEndState()
{
    vector<pgn::Ply> moves;
    moves.push_back(pgn::Ply("e4"));
    moves.push_back(pgn::Ply("e5"));

    GamePlayer player;
    player.setMoves(moves);
    player.goToEnd();

    QCOMPARE((int)player.chessBoard().getPiece(3, 4).type, (int)Pawn);
}

void PgntestTest::GamePlayer_ifMoveIsNotExistsReturnFalse()
{
    vector<pgn::Ply> moves;
    moves.push_back(pgn::Ply("e4"));

    GamePlayer player;
    player.setMoves(moves);

    QVERIFY(!player.goToMove(10));
}

void PgntestTest::Parser_ParseValidFile()
{
    bool exceptionThrowed = false;
    bool result = true;

    pgn::GameCollection games;

    std::string::const_iterator itr1 = validPgnGame.begin();
    std::string::const_iterator itr2 = validPgnGame.end();

    try
    {
        pgn::Parser parser;
        result = parser.getGameCollection(
                    itr1,
                    itr2,
                    games);
    }
    catch(...)
    {
        exceptionThrowed = true;
    }

    QVERIFY(!exceptionThrowed);
    QVERIFY(result);
    QVERIFY(games.size() == 1);
}

void PgntestTest::Parser_DoNotParseInvalidFile()
{
    bool exceptionThrowed = false;
    bool result = false;

    pgn::GameCollection games;

    std::string::const_iterator itr1 = invalidPgnGame.begin();
    std::string::const_iterator itr2 = invalidPgnGame.end();

    try
    {
        pgn::Parser parser;
        result = parser.getGameCollection(
                    itr1,
                    itr2,
                    games);
    }
    catch(...)
    {
        exceptionThrowed = true;
    }

    QVERIFY(exceptionThrowed);
    QVERIFY(!result);
}


QTEST_APPLESS_MAIN(PgntestTest);

#include "tst_pgntesttest.moc"
