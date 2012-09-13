#ifndef PGNEXPORTER_H
#define PGNEXPORTER_H


#include <QObject>
#include <QString>

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class PGNExporter : public QObject
{
Q_OBJECT

private:

public:

    PGNExporter(QObject* parent = NULL);

    bool exportToFile(const vector<int> gamesIds, const QString& fileName);

signals:
    void onProgress(int percent);

};

#endif // PGNEXPORTER_H
