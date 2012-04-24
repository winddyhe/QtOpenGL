#include "qterrain.h"

QTerrain::QTerrain()
{
    m_globalVertex = NULL;
    m_sectionVertex = NULL;
}

QTerrain::~QTerrain()
{
    safe_delete_array(m_globalVertex);
    safe_delete_array(m_sectionVertex);
}

void QTerrain::initial(QCubeEx &world, QString heightMapPath, QGLShaderProgram *program, GLuint tex)
{
    m_world = world;
    m_program = program;
    m_texture = tex;

    loadHeightMap(heightMapPath);

    createSectionVertexBuffer();
    calculateHeight();
    calculateNormal();
}

/*initial section data, vertex Pos xy and texcoord*/
void QTerrain::createSectionVertexBuffer()
{
    m_sectionVertex = new TSectionVertex[SECTION_SIZE * SECTION_SIZE];

    QVector3D worldSize = m_world.size();

    QVector2D cellSize(worldSize.x() / (m_size - 1), worldSize.z() / (m_size - 1));

    for(int i = 0; i < SECTION_SIZE; i++)
    {
        for(int j = 0; j < SECTION_SIZE; j++)
        {
            m_sectionVertex[i * SECTION_SIZE + j].posXY = QVector2D(i * cellSize.x(), j * cellSize.y());
            m_sectionVertex[i * SECTION_SIZE + j].texCoord =
                    QVector2D((float)i / (float)SECTION_SIZE, (float)j / (float)SECTION_SIZE);
        }
    }
}

/*limits: heightMap width = height, and width must be 2^n */
void QTerrain::loadHeightMap(QString heightMapPath)
{
    m_heightMap.load(heightMapPath);
    Q_ASSERT(heightMap.height() == heightMap.width());
    Q_ASSERT(!(heightMap.height() & heightMap.height() - 1));

    m_size = m_heightMap.width() + 1;
    m_globalVertex = new TGlobalVertex[m_size * m_size];
}

/*intial height data*/
void QTerrain::calculateHeight()
{
    if(!m_globalVertex)     return;

    for(int i = 0; i < m_size; i++)
    {
        for(int j = 0; j < m_size; j++)
        {
            m_globalVertex[i * m_size + j].height = calculateHeightInPixel(i , j);
        }
    }
}

/*calculate height value for pre position*/
float QTerrain::calculateHeightInPixel(int i, int j)
{
    if(i == m_size - 1)
    {
        i = m_size - 2;
    }
    if(j == m_size - 1)
    {
        j = m_size - 2;
    }

    QColor color = m_heightMap.pixel(m_size - 2 - i, j);
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    return (red + green + blue) / 3.0f;
}

/*calculate vertex's normal*/
void QTerrain::calculateNormal()
{
}

void QTerrain::render()
{

    m_lod->build(0.0f, 0.0f, (m_size-1) / 2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    m_program->setUniformValue("u_texture", 0);
}



















