#ifndef QNOLODQUAD_H
#define QNOLODQUAD_H

#include "qlod.h"
#include "qterrain.h"

class QTerrain;

class QNoLodQuad : public QLod
{
public:
    QNoLodQuad();

    void create(QTerrain *T);
    void build(int centerX, int centexY, int size);

private:
    void attachNode(int centerX, int centerY);

private:
    int m_nLevel;
};

#endif // QNOLODQUAD_H
