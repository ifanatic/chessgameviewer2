#include "pgnexporter.h"

#include <fstream>

#include "gamefinder.h"

PGNExporter::PGNExporter(QObject* parent) : QObject(parent)
{
}

bool PGNExporter::exportToFile(const vector<int> gamesIds, const QString& fileName)
{
    GameFinder finder;

    std::fstream outputFile(fileName.toStdString().c_str(), std::ios::out | std::ios::trunc);

//    outputFile.open();

    if(!outputFile.is_open())
    {
        return false;
    }

    for(size_t i = 0; i < gamesIds.size(); ++i)
    {
        outputFile << finder.getGameById(gamesIds[i]) << endl;

        emit onProgress((i + 1) * 100 / gamesIds.size());
    }

    emit onProgress(100);

    outputFile.close();

    return true;
}
