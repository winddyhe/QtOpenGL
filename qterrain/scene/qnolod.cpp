#include "qnolod.h"

#include "mem/dbg.h"

QNoLodQuad::QNoLodQuad()
{
    m_tileNum = 0;
    m_nLevel = 0;
    m_curLevel = 0;
    m_buildTriangles = 0;
    m_buildIndicesNumber = 0;
}

QNoLodQuad::~QNoLodQuad()
{
    safe_delete_array(m_indices);
}

void QNoLodQuad::init(QTerrain *T, QFrustum F)
{
    Q_UNUSED(F);
    m_pTerrain = T;
    m_pFrustum = &F;

    m_tileNum = m_pTerrain->m_sectionCountSq * m_pTerrain->m_sectionCountSq;

    int input = m_pTerrain->m_size - 1;
    int all_level = 0;

    qDebug() << "input =" << input;
    qDebug() << "all_level =" << all_level;

    while(!(input & 0x01))
    {
        input = input >> 1;
        all_level++;
    }
    m_nLevel = all_level;

    qDebug() << "m_nLevel =" << m_nLevel;
    qDebug() << "indices number:" << m_tileNum * (QTerrain::e_SectionSize - 1) / 2 * (QTerrain::e_SectionSize - 1) / 2 * 10;
    m_indices = new GLushort[m_tileNum * (QTerrain::e_SectionSize - 1) / 2 * (QTerrain::e_SectionSize - 1) / 2 * 10];
}


void QNoLodQuad::build()
{
    m_buildTriangles = 0;
    m_buildIndicesNumber = 0;
    QVector<NODE> next_nodes(1<<(m_nLevel-1));
    QVector<NODE> cur_nodes(1<<(m_nLevel-1));

    cur_nodes.clear();
    next_nodes.clear();

    //root node
    NODE root(1<<(m_nLevel-1), 1<<(m_nLevel-1));
//    qDebug() << "node root(" << root.x << "," << root.y << ")";

    cur_nodes.push_back(root);

    NODE child;

    for(int i = m_nLevel; i > 0; --i)
    {
        m_curLevel = i;

        for(int j = 0; j < cur_nodes.size(); ++j)
        {
            if(i >= 2)
            {
                int d = 1 <<(i-2);
//                qDebug() << "d =" << d;

                child.x = cur_nodes[j].x + d;
                child.y = cur_nodes[j].y + d;
                next_nodes.push_back(child);

                child.x = cur_nodes[j].x - d;
                child.y = cur_nodes[j].y + d;
                next_nodes.push_back(child);

                child.x = cur_nodes[j].x + d;
                child.y = cur_nodes[j].y - d;
                next_nodes.push_back(child);

                child.x = cur_nodes[j].x - d;
                child.y = cur_nodes[j].y - d;
                next_nodes.push_back(child);
            }
            else
            {
                attachNode(cur_nodes[j]);
//                qDebug() << "i =" << i;
            }
        }

        cur_nodes.clear();
        cur_nodes = next_nodes;
        next_nodes.clear();
    }
}

void QNoLodQuad::attachNode(const NODE& node)
{
    if(m_curLevel > QTerrain::e_SectionLevel)     return;

//    qDebug() << "attachNode...";
    qDebug() << m_curLevel;
    int IDX = node.x / (QTerrain::e_SectionSize - 1);
    int IDY = node.y / (QTerrain::e_SectionSize - 1);
    qDebug() << node.x << node.y;
    int ID = IDY * m_pTerrain->m_sectionCountSq + IDX;
    qDebug() << ID;
    int size = 1 << (m_curLevel - 1);

    Q_ASSERT(m_curLevel - 1 >= 0);
    Q_ASSERT(size <= (QTerrain::e_SectionSize >> 1));
    Q_ASSERT(ID < m_pTerrain->m_sectionCountSq * m_pTerrain->m_sectionCountSq);

    int tileSize = QTerrain::e_SectionSize;

    int cellX = node.x % (tileSize - 1);
    int cellY = node.y % (tileSize - 1);

    int i = m_buildIndicesNumber;

    m_indices[i++] = cellX + cellY * tileSize;                    //center

    m_indices[i++] = cellX - size + (cellY + size) * tileSize;    //left up

    m_indices[i++] = cellX + (cellY + size) * tileSize;           //center up

    m_indices[i++] = cellX + size + (cellY + size) * tileSize;    //right up

    m_indices[i++] = cellX + size + cellY * tileSize;             //right center

    m_indices[i++] = cellX + size + (cellY - size) * tileSize;    //right down

    m_indices[i++] = cellX + (cellY - size) * tileSize;           //center down

    m_indices[i++] = cellX - size + (cellY - size) * tileSize;    //left down

    m_indices[i++] = cellX - size + cellY * tileSize;             //left center

    m_indices[i++] = cellX - size + (cellY + size) * tileSize;    //left up

#if 0
    GLushort indices[10];

    int i = 0;

    indices[i++] = cellX + cellY * tileSize;                    //center
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX - size + (cellY + size) * tileSize;    //left up
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX + (cellY + size) * tileSize;           //center up
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX + size + (cellY + size) * tileSize;    //right up
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX + size + cellY * tileSize;             //right center
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX + size + (cellY - size) * tileSize;    //right down
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX + (cellY - size) * tileSize;           //center down
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX - size + (cellY - size) * tileSize;    //left down
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX - size + cellY * tileSize;             //left center
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    indices[i++] = cellX - size + (cellY + size) * tileSize;    //left up
//    qDebug() << "indices[" << i-1 <<"] =" << indices[i - 1];

    Q_ASSERT(i <= 10);
#endif

    /*draw terrain*/
//    qDebug() << "TileID =" << ID;
    m_pTerrain->setShaderVaribles(ID);

    int heightLoc = m_pTerrain->m_program->attributeLocation("a_posHeight");
    glVertexAttribPointer(heightLoc, 1, GL_FLOAT, GL_FALSE,
                          sizeof(QTerrain::TVertex), m_pTerrain->m_pSections[ID].tileVertices);
    m_pTerrain->m_program->enableAttributeArray("a_posHeight");

    int normalLoc = m_pTerrain->m_program->attributeLocation("a_normal");
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(QTerrain::TVertex),
                          m_pTerrain->m_pSections[ID].tileVertices + sizeof(float));
    m_pTerrain->m_program->enableAttributeArray("a_normal");

    glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_SHORT, (const void*)m_indices);//[m_buildIndicesNumber])

    m_buildTriangles += i-2;      //number of trianles
    m_buildIndicesNumber += 10;
}

#if 0
void QNoLodQuad::build(int tileID, int centerX, int centerY, int size)
{
    if(size > 2)
    {
        build(tileID, centerX - size / 2, centerY + size / 2, size / 2);
        build(tileID, centerX + size / 2, centerY + size / 2, size / 2);
        build(tileID, centerX - size / 2, centerY - size / 2, size / 2);
        build(tileID, centerX + size / 2, centerY - size / 2, size / 2);
    }
    else    //render
    {
        GLushort indices[10];

        int tileSize = m_pTerrain->e_SectionSize;

        int cellX = centerX % (tileSize - 1);
        int cellY = centerY % (tileSize - 1);

        int i = 0;

        indices[i++] = cellX + cellY * tileSize;                    //center

        indices[i++] = cellX - size + (cellY + size) * tileSize;    //left up

        indices[i++] = cellX + (cellY + size) * tileSize;           //center up

        indices[i++] = cellX + size + (cellY + size) * tileSize;    //right up

        indices[i++] = cellX + size + cellY * tileSize;             //right center

        indices[i++] = cellX + size + (cellY - size) * tileSize;    //right down

        indices[i++] = cellX + (cellY - size) * tileSize;           //center down

        indices[i++] = cellX - size + (cellY - size) * tileSize;    //left down

        indices[i++] = cellX - size + cellY * tileSize;             //left center

        indices[i++] = cellX - size + (cellY + size) * tileSize;    //left up

        Q_ASSERT(i <= 10);

        /*draw terrain*/
        m_pTerrain->setShaderVaribles(tileID);

        glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_SHORT, indices);
    }
}
#endif
