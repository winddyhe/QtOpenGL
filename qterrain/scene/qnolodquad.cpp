#include "qnolodquad.h"

QNoLodQuad::QNoLodQuad()
{
    m_nLevel = 0;
}

void QNoLodQuad::create(QTerrain *T)
{
    m_terrain = T;

    int size = m_terrain->m_size - 1;
    int level = 0;
    while(size >> 1)
    {
        level++;
    }
    m_nLevel = level;
}

void QNoLodQuad::build(int centerX, int centexY, int size)
{
    if(m_nLevel >= 2)
    {
        m_nLevel--;
        build(centerX - size / 2, centerY - size / 2, size / 2);
        build(centerX - size / 2, centerY + size / 2, size / 2);
        build(centerX + size / 2, centerY + size / 2, size / 2);
        build(centerX + size / 2, centerY - size / 2, size / 2);
    }
    else
    {
        attachNode(centerX, centexY);
    }
}
void QNoLodQuad::attachNode(int centerX, int centerY)
{
    Q_ASSERT(m_nLevel == 1);

    int x = centerX % (SECTION_SIZE - 1);
    int y = centerY % (SECTION_SIZE - 1);

    QVector<TSectionVertex> sectionVertexVec;
    sectionVertexVec << m_terrain->m_sectionVertex[ x      * SECTION_SIZE + y];
    sectionVertexVec << m_terrain->m_sectionVertex[(x - 1) * SECTION_SIZE + y + 1];
    sectionVertexVec << m_terrain->m_sectionVertex[ x      * SECTION_SIZE + y + 1];
    sectionVertexVec << m_terrain->m_sectionVertex[(x + 1) * SECTION_SIZE + y + 1];
    sectionVertexVec << m_terrain->m_sectionVertex[(x + 1) * SECTION_SIZE + y];
    sectionVertexVec << m_terrain->m_sectionVertex[(x + 1) * SECTION_SIZE + y - 1];
    sectionVertexVec << m_terrain->m_sectionVertex[ x      * SECTION_SIZE + y - 1];
    sectionVertexVec << m_terrain->m_sectionVertex[(x - 1) * SECTION_SIZE + y - 1];
    sectionVertexVec << m_terrain->m_sectionVertex[(x - 1) * SECTION_SIZE + y];
    sectionVertexVec << m_terrain->m_sectionVertex[(x - 1) * SECTION_SIZE + y + 1];

    QVector<TGlobalVertex> globalVertexVec;
    globalVertexVec << m_terrain->m_globalVertex[ centerX      * m_terrain->m_size + centerY];
    globalVertexVec << m_terrain->m_globalVertex[(centerX - 1) * m_terrain->m_size + centerY + 1];
    globalVertexVec << m_terrain->m_globalVertex[ centerX      * m_terrain->m_size + centerY + 1];
    globalVertexVec << m_terrain->m_globalVertex[(centerX + 1) * m_terrain->m_size + centerY + 1];
    globalVertexVec << m_terrain->m_globalVertex[(centerX + 1) * m_terrain->m_size + centerY];
    globalVertexVec << m_terrain->m_globalVertex[(centerX + 1) * m_terrain->m_size + centerY - 1];
    globalVertexVec << m_terrain->m_globalVertex[ centerX      * m_terrain->m_size + centerY - 1];
    globalVertexVec << m_terrain->m_globalVertex[(centerX - 1) * m_terrain->m_size + centerY - 1];
    globalVertexVec << m_terrain->m_globalVertex[(centerX - 1) * m_terrain->m_size + centerY];
    globalVertexVec << m_terrain->m_globalVertex[(centerX - 1) * m_terrain->m_size + centerY + 1];

    m_terrain->m_program->setUniformValue("u_startPos", QVector2D(0.0f, 0.0f));

    int posXYLoc = m_terrain->m_program->attributeLocation("a_position");
    glVertexAttribPointer(posXYLoc, 2, GL_FLOAT, GL_FALSE, sizeof(TSectionVertex), sectionVertexVec.constData());
    m_terrain->m_program->enableAttributeArray("a_position");

    int texcoordLoc = m_terrain->m_program->attributeLocation("a_texcoord");
    glVertexAttribPointer(texcoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(TSectionVertex),
                          sectionVertexVec.constData() + sizeof(QVector2D));
    m_terrain->m_program->enableAttributeArray("a_texcoord");

    int heightLoc = m_terrain->m_program->attributeLocation("a_height");
    glVertexAttribPointer(heightLoc, 1, GL_FLOAT, GL_FALSE, sizeof(TGlobalVertex), globalVertexVec.constData());
    m_terrain->m_program->enableAttributeArray("a_height");

    glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
}

