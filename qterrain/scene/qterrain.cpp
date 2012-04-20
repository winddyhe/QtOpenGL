#include "qterrain.h"

#include <QDebug>
#include "mem/dbg.h"

QTerrain::QTerrain()
{
    m_texture = 0;
    m_program = NULL;
    m_pSections = NULL;
    m_heightTable = NULL;
    m_normalTable = NULL;
    m_size = 0;
    m_sectionCountSq = 0;
}

QTerrain::~QTerrain()
{
    m_size = 0;
    m_sectionCountSq = 0;
    m_noLod = NULL;

    safe_delete_array(m_pSections);
    safe_delete_array(m_heightTable);
    safe_delete_array(m_normalTable);

    safe_delete_array(m_pVertXYandCoord);

    for(int i = 0; i < m_sectionCountSq*m_sectionCountSq; i++)
    {
        safe_delete_array(m_pSections[i].tileVertices);
    }
    safe_delete_array(m_pSections);
}

bool QTerrain::create(QGLShaderProgram *program, GLuint tex, int size,
                      QString heightMap, const QCubeEx &world)
{
    /*check size value whether pow of 2*/

    m_program = program;
    m_texture = tex;
    m_size = size;
    m_rtWorld = world;

    bool re = true;

    //load height map data
    re = loadHeightMap(heightMap);
    if(!re)
    {
        qDebug() << "Load height map failed!";
        return false;
    }

    //caculate normal map
    re = calculateNormalMap();
    if(!re)
    {
        qDebug() << "Caculate normal failed!";
        return false;
    }

    //create terrain data buffer
    re = createBuffer();
    if(!re)
    {
        qDebug() << "Create buffer failed!";
    }
    return true;
}

bool QTerrain::loadHeightMap(QString heightMap)
{
    //map size 2^n + 1
    int factSize = m_size + 1;

    QImage heightImage(heightMap);

    if(!m_heightTable)
    {
        safe_delete_array(m_heightTable);
    }

    m_heightTable = new float[factSize * factSize];
    qDebug() << "map size=" << m_size;
    int test = 0;
    for(int j = m_size - 1; j >= 0; --j)
    {
        int i;
        for(i = 0; i <= m_size-1; ++i)
        {
            m_heightTable[j*(m_size+1)+i] = calculateHeight(heightImage, i, j);
            test++;
        }
        m_heightTable[j*(m_size+1)+i+1] = calculateHeight(heightImage, i-1, j);
        test++;
    }
    for(int i = 0; i < m_size + 1; i++)
    {
        m_heightTable[m_size*(m_size+1)+i] = m_heightTable[(m_size-1)*(m_size+1)+i];
        test++;
    }

    qDebug() << "test=" << test << ", facesize*facesize=" << factSize * factSize;

    Q_ASSERT(test == factSize * factSize);
    m_size = factSize;

    return true;
}

float QTerrain::calculateHeight(QImage &image, int x, int y)
{
    QColor color = image.pixel(x, y);
    int r = color.red();
    int g = color.green();
    int b = color.blue();

    float h = (r+g+b) / 3.0;

    return h;
}

bool QTerrain::calculateNormalMap()
{
    if(!m_normalTable)
    {
        safe_delete_array(m_normalTable);
    }

    m_normalTable = new QVector3D[m_size * m_size];

    for(int y = 0; y < m_size; y++)
    {
        for(int x = 0; x < m_size; x++)
        {

            QVector3D left(0.0f, 0.0f, 0.0f);
            QVector3D right(0.0f, 0.0f, 0.0f);
            QVector3D up(0.0f, 0.0f, 0.0f);
            QVector3D down(0.0f, 0.0f, 0.0f);

            QVector3D cur = getPos(x, y);

            if(x>0)         left  = getPos(x-1, y) - cur;
            if(x+1<m_size)  right = getPos(x+1, y) - cur;
            if(y+1<m_size)  up    = getPos(x, y+1) - cur;
            if(y>0)         down  = getPos(x, y-1) - cur;

            QVector3D lu, ru, ld, rd;

            lu = QVector3D::crossProduct(left, up);
            ru = QVector3D::crossProduct(up, right);
            ld = QVector3D::crossProduct(down, left);
            rd = QVector3D::crossProduct(right, down);

            int average = 0;
            if(x>0 && y>0)                  {ld.normalize(); average++;}
            if(x>0 && y+1<m_size)           {lu.normalize(); average++;}
            if(y>0 && x+1<m_size)           {rd.normalize(); average++;}
            if(x+1<m_size && y+1<m_size)    {ru.normalize(); average++;}

            int index = y*m_size + x;

            QVector3D cur_normal = (lu+ru+ld+rd)/(float)average;

            cur_normal.normalize();

            m_normalTable[index] = cur_normal;
        }
    }
    return true;
}

bool QTerrain::createBuffer()
{
    qDebug() << "createBuffer()...";

    /*create vertex buffer*/
    m_pVertXYandCoord = new TSectionVertex[e_SectionSize * e_SectionSize];
    QVector3D worldSize = m_rtWorld.size();
    QVector2D cellSize(worldSize.x()/(m_size-1), worldSize.z()/(m_size-1));
    QVector2D set(0.0f, 0.0f);

    for(int y = 0; y < e_SectionSize; y++)
    {
        set = QVector2D(0.0f, y*cellSize.y());

        for(int x = 0; x < e_SectionSize; x++)
        {
            m_pVertXYandCoord[y*e_SectionSize+x].xyPos = set;
            m_pVertXYandCoord[y*e_SectionSize+x].st =
                    QVector2D((float)x/(float)(e_SectionSize-1),
                              (float)y/(float)(e_SectionSize-1));

            set.setX(set.x() + cellSize.x());
        }
    }

    /*create terrain sections*/
    int tileCount = 0;
    tileCount = (m_size-1)/(e_SectionSize-1);
    qDebug() << tileCount;
    m_sectionCountSq = tileCount;
    qDebug() << "m_sectionCountSq =" << m_sectionCountSq;
    tileCount = tileCount * tileCount;

    m_pSections = new TTerrainSection[tileCount];

    for(int i = 0; i < tileCount; i++)
    {
        createSectionsBuffer(i);
    }
    return true;
}

bool QTerrain::createSectionsBuffer(int tileID)
{
    Q_ASSERT(tileID < m_sectionCountSq*m_sectionCountSq);

    m_pSections[tileID].tileVertices = new TVertex[e_SectionSize * e_SectionSize];

    for(int y = 0; y < e_SectionSize; y++)
    {
        for(int x = 0; x < e_SectionSize; x++)
        {
            Q_ASSERT(y*e_SectionSize + x < e_SectionSize * e_SectionSize);
            m_pSections[tileID].tileVertices[y*e_SectionSize+x].height = getTileHeight(tileID, x, y);
            m_pSections[tileID].tileVertices[y*e_SectionSize+x].normal = getTileNormal(tileID, x, y);
        }
    }

    return true;
}

void QTerrain::render(const QFrustum &frustum)
{
    Q_ASSERT(m_noLod);

    Q_UNUSED(frustum);

    //each section share xy and texcoord data
    int posXYLoc = m_program->attributeLocation("a_posXY");
    glVertexAttribPointer(posXYLoc, 2, GL_FLOAT, GL_FALSE,
                          sizeof(TSectionVertex), m_pVertXYandCoord);
    m_program->enableAttributeArray("a_posXY");

    int texcLoc = m_program->attributeLocation("a_texCoord");
    glVertexAttribPointer(texcLoc, 2, GL_FLOAT, GL_FALSE,
                          sizeof(TSectionVertex), m_pVertXYandCoord + sizeof(QVector2D));
    m_program->enableAttributeArray("a_posXY");

    m_noLod->build();
//    qDebug() << "IndicesNumber =" << m_noLod->getIndicesNumber();
//    qDebug() << "TriangleNumber =" << m_noLod->getTriangleNumber();

    /*set tex*/
    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    m_program->setUniformValue("u_texture", 0);
}


