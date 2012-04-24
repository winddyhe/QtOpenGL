#ifndef QTERRAIN_H
#define QTERRAIN_H

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QGLShaderProgram>

#include "math/qcubeex.h"
#include "common/qcommon.h"
#include "scene/qlod.h"
#include "scene/qnolodquad.h"

class QLod;
class QNoLodQuad;

//共享xy和tex的数据，这样做节省了不小的内存空间
/*
    一小单块的xy和纹理坐标，所有的地形块均是使用该数据
    只是最后加上相应的地形块的偏移值
*/
struct TSectionVertex
{
    QVector2D posXY;
    QVector2D texCoord;
};

/*
    整个地形的高度和向量值
*/
struct TGlobalVertex
{
    float height;
    QVector3D normal;
};

#define SECTION_LEVEL   6
#define SECTION_SIZE    ((1 << SECTION_LEVEL) + 1)

class QTerrain
{
public:
    QTerrain();
    ~QTerrain();

    void initial(QCubeEx& world, QString heightMapPath, QGLShaderProgram* program, GLuint tex);
    void render();

    void setLodType(QLod* lod);

    friend class QNoLodQuad;
private:
    void createSectionVertexBuffer();

    void calculateHeight();
    void calculateNormal();

    void loadHeightMap(QString heightMapPath);
    float calculateHeightInPixel(int i, int j);

private:
    TSectionVertex* m_sectionVertex;
    TGlobalVertex*  m_globalVertex;

    QGLShaderProgram* m_program;
    GLuint m_texture;

    QLod*   m_lod;
    QCubeEx m_world;
    int m_size;
    QImage m_heightMap;

    int m_tileCountSqrt;
};

inline void QTerrain::setLodType(QLod *lod)
{
    m_lod = lod;
}

#endif // QTERRAIN_H
