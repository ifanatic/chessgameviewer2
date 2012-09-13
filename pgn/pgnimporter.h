#ifndef PGNIMPORTER_H
#define PGNIMPORTER_H

#include <QObject>
#include <QString>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "gamevollection.h"

class PGNImporter : public QObject
{
Q_OBJECT

private:

public:
    PGNImporter(QObject* parent = NULL);

    bool import(pgn::GameCollection& games);
    bool importFromFile(const QString& fileName);

signals:
    void onProgress(int percent);
};

#endif // PGNIMPORTER_H
