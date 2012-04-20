#ifndef QNOLOD_H
#define QNOLOD_H

#include "qterrain.h"
#include "common/qfrustum.h"

#include <QVector>

class QTerrain;


#define BUFFER_OFFSET(offset)   ( (GLushort*)NULL + (offset) )

/*use quad-tree to manage the indices of terrain*/
class QNoLod
{
public:
    virtual void init(QTerrain *T, QFrustum F) = 0;
    virtual void build() = 0;
    virtual int  getTriangleNumber() = 0;
    virtual int  getIndicesNumber() = 0;

protected:
    QTerrain *m_pTerrain;
    QFrustum *m_pFrustum;
};

class QNoLodQuad : public QNoLod
{
private:
    struct NODE
    {
        int x, y;
        NODE(int _x, int _y) : x(_x), y(_y) {}
        NODE() {}
    };

public:
    QNoLodQuad();
    ~QNoLodQuad();

    void init(QTerrain *T, QFrustum F);
#if 0
    void build(int tileID, int centerX, int centerY, int size);
#endif
    void build();
    void attachNode(const NODE& node);
    int  getTriangleNumber()    { return m_buildTriangles; }
    int  getIndicesNumber()     { return m_buildIndicesNumber; }

private:
    int m_tileNum;
    int m_nLevel;
    int m_curLevel;

    int m_buildTriangles;
    int m_buildIndicesNumber;

    GLushort *m_indices;
};

#endif // QNOLOD_H
