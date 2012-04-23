#ifndef QTERRAIN_H
#define QTERRAIN_H

#include <QVector3D>

struct TTrerrainNode
{

};

class QTerrain
{
public:
    QTerrain();
    ~QTerrain();

    void loadTerrainFromHeightMap(QString heightMapFileName);

private:

};

#endif // QTERRAIN_H
