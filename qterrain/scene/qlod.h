#ifndef QLOD_H
#define QLOD_H

#include "scene/qterrain.h"

class QTerrain;

class QLod
{
public:
    virtual void create(QTerrain* T) = 0;
    virtual void build(int centerX, int centexY, int size) = 0;

protected:
    QTerrain* m_terrain;
};

#endif // QLOD_H
