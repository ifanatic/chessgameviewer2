#include <QApplication>

#include "gamevollection.h"
#include "exception.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "chessboard.h"
#include "fenform.h"
#include "pgnimporter.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include "chessboardview.h"

#include "mainwindow.h"

#include <QTextCodec>
#include "chessdbconnection.h"

#include "gamefinder.h"
#include "pgnexporter.h"

using namespace std;

int main(int argc, char *argv[])
{
    FENForm ff;

    QApplication app(argc, argv);

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");

    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);

    ChessDbConnection::open();
    if(!ChessDbConnection::isOpened())
    {
        std::cerr << "ERROR: Database open failed" << endl;
    }

    vector<int> ids;
    ids.push_back(1);
    ids.push_back(2);
    ids.push_back(3);

//    PGNExporter exporter;
//    exporter.exportToFile(ids, "/home/fanatic/1.pgn");

//    GameFinder finder;
//    cout << finder.getGameById(123) << endl;

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
