#include "pgnimporter.h"

#include <fstream>
#include <vector>
#include <sstream>

#include <QString>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlResult>
#include <QSqlRecord>

#include <iostream>

#include "chessboard.h"
#include "fenform.h"

#include "gamegateway.h"
#include <QMessageBox>
#include "exception.h"

PGNImporter::PGNImporter(QObject* parent) : QObject(parent)
{
}

bool PGNImporter::import(pgn::GameCollection& games)
{

    int currentGame = 0;

    QSqlDatabase db = QSqlDatabase::database();
    db.driver()->beginTransaction();

    try
    {
    FENForm fenForm;

    pgn::GameCollection::iterator gameIter;
    for (gameIter = games.begin(); gameIter != games.end(); gameIter++)
    {
        GameGateway gameGateway;
        gameGateway.insertGame(*gameIter);

        emit onProgress((++currentGame) * 100 / games.size());
    }

    cout << "Count: " << currentGame << endl;

    }
    catch(...)
    {
        db.driver()->rollbackTransaction();
        return false;
    }

    if(!db.driver()->commitTransaction())
    {
         std::cerr << "ERROR: !Commit" << db.lastError().driverText().toStdString() << endl;
    }

    return true;
}

bool PGNImporter::importFromFile(const QString& fileName)
{
    pgn::GameCollection games;

    std::ifstream pgnfile(fileName.toStdString().c_str());

    std::cout << "\"" << fileName.toStdString() << "\"" << std::endl;
    std::cout << "Called: " << pgnfile.is_open() << std::endl;
    emit onProgress(1);


    try
    {
        pgnfile >> games;
    }
    catch(pgn::ParseException& ex)
    {
        std::clog << "Parse error: " << ex.what() << std::endl;

        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setText(QString("Parse error: \"%1\" - document can not be imported").arg(ex.what()));
        msg.exec();

        return false;
    }

    return import(games);
}
