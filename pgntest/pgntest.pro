#-------------------------------------------------
#
# Project created by QtCreator 2012-02-15T18:15:16
#
#-------------------------------------------------

QT       += sql testlib

TARGET = tst_pgntesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_pgntesttest.cpp \
    ../pgn/utils.cpp \
    ../pgn/rookmovechecker.cpp \
    ../pgn/queenmovechecker.cpp \
    ../pgn/taglist.cpp \
    ../pgn/tag.cpp \
    ../pgn/square.cpp \
    ../pgn/ply.cpp \
    ../pgn/piece.cpp \
    ../pgn/parser.cpp \
    ../pgn/movelist.cpp \
    ../pgn/move.cpp \
    ../pgn/pgnimporter.cpp \
    ../pgn/gameresult.cpp \
    ../pgn/gamecollection.cpp \
    ../pgn/gamegateway.cpp \
    ../pgn/game.cpp \
    ../pgn/exception.cpp \
    ../pgn/commenttext.cpp \
    ../pgn/pawnmovechecker.cpp \
    ../pgn/movecheckersrepository.cpp \
    ../pgn/knightmovechecker.cpp \
    ../pgn/kingmovechecker.cpp \
    ../pgn/gameplayer.cpp \
    ../pgn/fenform.cpp \
    ../pgn/directionmovechecker.cpp \
    ../pgn/chessboardview.cpp \
    ../pgn/chessboard.cpp \
    ../pgn/bishopmovechecker.cpp \
    ../pgn/basicmovechecker.cpp \
    ../pgn/piecepathtracer.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

OTHER_FILES +=
INCLUDEPATH += ../pgn

HEADERS += \
    ../pgn/utils.h \
    ../pgn/rookmovechecker.h \
    ../pgn/queenmovechecker.h \
    ../pgn/taglist.h \
    ../pgn/tag.h \
    ../pgn/square.h \
    ../pgn/ply.h \
    ../pgn/piece.h \
    ../pgn/parser.h \
    ../pgn/moveList.h \
    ../pgn/move.h \
    ../pgn/pgnimporter.h \
    ../pgn/gameresult.h \
    ../pgn/gamevollection.h \
    ../pgn/game.h \
    ../pgn/gamegateway.h \
    ../pgn/exception.h \
    ../pgn/commentText.h \
    ../pgn/pawnmovechecker.h \
    ../pgn/movecheckersrepository.h \
    ../pgn/knightmovechecker.h \
    ../pgn/kingmovechecker.h \
    ../pgn/gameplayer.h \
    ../pgn/fenform.h \
    ../pgn/directionmovechecker.h \
    ../pgn/chessboardview.h \
    ../pgn/chessboard.h \
    ../pgn/bishopmovechecker.h \
    ../pgn/basicmovechecker.h \
    ../pgn/piecepathtracer.h

FORMS +=

RESOURCES +=















