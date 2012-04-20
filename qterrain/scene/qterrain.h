#ifndef QTERRAIN_H
#define QTERRAIN_H

#include <QtOpenGL>
#include <QGLShaderProgram>
#include <QImage>
#include <QVector3D>

#include "common/qcommon.h"
#include "common/qcubeex.h"
#include "common/qfrustum.h"

#include "scene/qnolod.h"

class QNoLod;
class QNoLodQuad;

/*
    terrain class
    Disc:   Divide the terrain into some sections. Each section can share vertex data
    if divide terrain to 129*129 and terrain size is 1024 * 1024, the sections has
    16*16
*/

class QTerrain
{

private:
    //per sections vertex data
    struct TSectionVertex
    {
        QVector2D xyPos;
        QVector2D st;
    };

    //global vertex data
    struct TVertex
    {
        float height;
        QVector3D normal;
    };

    struct TTerrainSection
    {
        TVertex *tileVertices;
    };

    enum eConstants
    {
        e_SectionLevel = 6,
        e_SectionSize = (1<<e_SectionLevel)+1
    };

public:
    QTerrain();
    ~QTerrain();

    bool create(QGLShaderProgram *program,
                GLuint tex,
                int size,
                QString heightMap,
                const QCubeEx& world);

    void render(const QFrustum &frustum);

    float               getHeight(int x, int y)     const;              //get height
    QVector3D           getPos(int x, int y)        const;              //get position
    int                 getIndex(int tileID, int x, int y) const;       //get index
    float               getTileHeight(int tileID, int x, int y);        //get a tile of assign pos's height
    const QVector3D&    getTileNormal(int tileID, int x, int y) const;  //get a tile of assign normal
    int                 getSize() const;
    QCubeEx             getWorld() const;
    void                setShaderVaribles(int tileId);                  //set shader uniform value
    void                setLodType(QNoLod* lod);

    friend class QNoLodQuad;

private:
    bool loadHeightMap(QString heightMap);      //load HeightMap
    bool calculateNormalMap();                  //calculate normal vector
    bool createBuffer();                        //create terrain data
    bool createSectionsBuffer(int tileID);      //create not shared terrain data

    float calculateHeight(QImage &image, int x, int y);

private:
    GLuint              m_texture;              //terrain texture
    QGLShaderProgram*   m_program;              //gl shader program

    TSectionVertex*     m_pVertXYandCoord;
    TTerrainSection*    m_pSections;            //terrain sections

    float*              m_heightTable;          //height table
    QVector3D*          m_normalTable;          //normal table

    int                 m_size;                 //map size (width = height)
    int                 m_sectionCountSq;       //section size

    QCubeEx             m_rtWorld;              //world coordinate space

    QNoLod      *m_noLod;
};

/*inline functions*/
inline int QTerrain::getIndex(int tileID, int x, int y) const
{
    Q_ASSERT(tileID < m_sectionCountSq * m_sectionCountSq
             && x < e_SectionSize && y < e_SectionSize);

    return (tileID / m_sectionCountSq * (1 << e_SectionLevel) + y) * m_size +
            tileID % m_sectionCountSq * (1 << e_SectionLevel) + x;
}

inline float QTerrain::getTileHeight(int tileID, int x, int y)
{
    return m_heightTable[getIndex(tileID, x, y)];
}

inline const QVector3D& QTerrain::getTileNormal(int tileID, int x, int y) const
{
    return m_normalTable[getIndex(tileID, x, y)];
}

inline QVector3D QTerrain::getPos(int x, int y) const
{
    QVector3D worldSize = m_rtWorld.size();

    QVector2D cellSize(worldSize.x() / (m_size-1), worldSize.z() / (m_size-1));

    float posX = m_rtWorld.pos0.x() + y*cellSize.x();
    float posZ = m_rtWorld.pos0.z() + y*cellSize.y();

    return QVector3D(posX, getHeight(x, y), posZ);
}

inline float QTerrain::getHeight(int x, int y) const
{
    return m_heightTable[x + y * m_size];
}

inline int QTerrain::getSize() const
{
    return m_size;
}

inline QCubeEx QTerrain::getWorld() const
{
    return m_rtWorld;
}

inline void QTerrain::setShaderVaribles(int tileId)
{
    Q_ASSERT(tileId < m_sectionCountSq*m_sectionCountSq);

    QVector3D worldSize = m_rtWorld.size();
    QVector2D sectionSize(worldSize.x() / (m_size - 1) * (1<<e_SectionLevel),
                          worldSize.z() / (m_size - 1) * (1<<e_SectionLevel));

    int y = tileId / m_sectionCountSq;
    int x = tileId % m_sectionCountSq;

    QVector2D pos;
    pos.setX(m_rtWorld.pos0.x() + x * sectionSize.x());
    pos.setY(m_rtWorld.pos0.z() + y * sectionSize.y());

//    qDebug() << "u_posOffset: " << pos;
    m_program->setUniformValue("u_posOffset", pos);
}

inline void QTerrain::setLodType(QNoLod *lod)
{
    m_noLod = lod;
}

#endif // QTERRAIN_H
