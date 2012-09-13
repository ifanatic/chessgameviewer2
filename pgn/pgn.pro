#-------------------------------------------------
#
# Project created by QtCreator 2012-02-14T00:18:17
#
#-------------------------------------------------

QT       += core sql gui

TARGET = pgn
# CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    chessboard.cpp \
    basicmovechecker.cpp \
    pawnmovechecker.cpp \
    knightmovechecker.cpp \
    bishopmovechecker.cpp \
    directionmovechecker.cpp \
    rookmovechecker.cpp \
    queenmovechecker.cpp \
    kingmovechecker.cpp \
    fenform.cpp \
    movecheckersrepository.cpp \
    utils.cpp \
    mainwindow.cpp \
    pgnimporter.cpp \
    chessboardview.cpp \
    gameplayer.cpp \
    taglist.cpp \
    tag.cpp \
    square.cpp \
    ply.cpp \
    piece.cpp \
    parser.cpp \
    move.cpp \
    pgnexporter.cpp\
    gameresult.cpp \
    game.cpp \
    gamecollection.cpp \
    exception.cpp \
    commentText.cpp \
    chessdbconnection.cpp \
    gamefinder.cpp \
    movelist.cpp \
    gamegateway.cpp \
    positionstatdialog.cpp \
    statprovider.cpp \
    piecepathtracer.cpp \
    piecepathdialog.cpp \
    piecepathview.cpp



HEADERS += \
    chessboard.h \
    basicmovechecker.h \
    pawnmovechecker.h \
    knightmovechecker.h \
    bishopmovechecker.h \
    directionmovechecker.h \
    rookmovechecker.h \
    queenmovechecker.h \
    kingmovechecker.h \
    fenform.h \
    utils.h \
    movecheckersrepository.h \
    mainwindow.h \
    pgnimporter.h \
    chessboardview.h \
    gameplayer.h \
    taglist.h \
    tag.h \
    square.h \
    ply.h \
    piece.h \
    parser.h \
    move.h \
    pgnexporter.h \
    movelist.h \
    gameresult.h \
    gamevollection.h \
    game.h \
    exception.h \
    commenttext.h \
    chessdbconnection.h \
    gamefinder.h \
    gamegateway.h \
    positionstatdialog.h \
    statprovider.h \
    positionstat.h \
    piecepathtracer.h \
    piecepathdialog.h \
    piecepathview.h


FORMS += \
    mainwindow.ui \
    positionstatdialog.ui \
    piecepathdialog.ui

RESOURCES += \
    resources.qrc










































































































