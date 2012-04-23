#include "qebtimewheel.h"

#include <QDebug>

QEBTimeWheel::QEBTimeWheel(QObject *parent) :
    QObject(parent)
{
    m_pVboIds = new GLuint[2];
    m_iIndicesNum = 0;
}

QEBTimeWheel::~QEBTimeWheel()
{
    glDeleteBuffers(2, m_pVboIds);
    delete[] m_pVboIds;
}

void QEBTimeWheel::initTimeWheelDatas(int width, int height, int faceNums)
{
    glGenBuffers(2, m_pVboIds);

    QVector<ebTimeWheelVertex> vertices;

    float angle = M_PI * 2 / faceNums;

    int radius = width / 2.0f / sin(angle / 2.0f);

    for(int i = 0; i < faceNums + 1; i++)
    {
        ebTimeWheelVertex vertex;
        vertex.position.setX(radius * cos(-angle / 2 + angle * i));
        vertex.position.setY(radius * sin(-angle / 2 + angle * i));
        vertex.position.setZ(0);
        vertex.texCoord.setX(0.0f);
        vertex.texCoord.setY(1 - 0.1f * i);
        vertices << vertex;
        qDebug() << vertex.position << vertex.texCoord;

        vertex.position.setX(radius * cos(-angle / 2 + angle * i));
        vertex.position.setY(radius * sin(-angle / 2 + angle * i));
        vertex.position.setZ(-height);
        vertex.texCoord.setX(1.0f);
        vertex.texCoord.setY(1 - 0.1f * i);
        vertices << vertex;
        qDebug() << vertex.position << vertex.texCoord;
    }

    m_iIndicesNum = faceNums * 6;
    GLushort *indices = new GLushort[m_iIndicesNum];
    int k = 0;
    for(int i = 0; i < faceNums; i++)
    {
        /*
          anti colckwise
          A--B
          |  |
          C--D
        */
        indices[k]      = i * 2;            //A
        indices[k + 1]  = i * 2 + 2;        //C
        indices[k + 2]  = i * 2 + 1;        //B

        indices[k + 3]  = i * 2 + 1;        //B
        indices[k + 4]  = i * 2 + 2;        //C
        indices[k + 5]  = i * 2 + 3;        //D

        qDebug() << indices[k]   << ", " << indices[k+1] <<", " << indices[k+2] <<", "
                 << indices[k+3] << ", " << indices[k+4] <<", " << indices[k+5];
        k = k + 6;
    }

//    /*index of last faces*/
//    indices[k]      = (faceNums - 1) * 2;
//    indices[k + 1]  = 0;
//    indices[k + 2]  = (faceNums - 1) * 2 + 1;
//    indices[k + 3]  = (faceNums - 1) * 2 + 1;
//    indices[k + 4]  = 0;
//    indices[k + 5]  = 1;

//    qDebug() << indices[k]   << ", " << indices[k+1] <<", " << indices[k+2] <<", "
//             << indices[k+3] << ", " << indices[k+4] <<", " << indices[k+5];

    qDebug() << "Vertices number:" << vertices.count();
    qDebug() << "Indices number: " << m_iIndicesNum;

    glBindBuffer(GL_ARRAY_BUFFER, m_pVboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.count() * sizeof(ebTimeWheelVertex), vertices.constData(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pVboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndicesNum * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

void QEBTimeWheel::drawTimeWheel(QGLShaderProgram &program, GLuint tex)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_pVboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pVboIds[1]);

    int offset = 0;
    int positionLoc = program.attributeLocation("a_position");
    program.enableAttributeArray(positionLoc);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(ebTimeWheelVertex), (const void*)offset);

    offset += sizeof(QVector3D);

    int texCoordLoc = program.attributeLocation("a_texcoord");
    program.enableAttributeArray(texCoordLoc);
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(ebTimeWheelVertex), (const void*)offset);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    program.setUniformValue("u_texture0", 0);
    program.setUniformValue("u_bMultiTexture", false);
    glDrawElements(GL_TRIANGLES, m_iIndicesNum, GL_UNSIGNED_SHORT, 0);
}


















