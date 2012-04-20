#ifndef QTGLWINDOW_H
#define QTGLWINDOW_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QTime>

#include "scene/qterrain.h"
#include "qcamera.h"
#include "scene/qnolod.h"

const static QString imagesPath[] =
{
    ":/images/grass2.jpg",
};

enum textureIndex
{
    grassIndex,

    textureCount
};


class QtGLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit QtGLWindow(QWidget *parent = 0);
    virtual ~QtGLWindow();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *e);

    void initShaders(QGLShaderProgram &program ,QString vshaderPath, QString fshaderPath);

protected:

    void useCurrentProgram(QGLShaderProgram &program);

    void initTextures();
    GLuint loadTexture(QString texPath);

    bool initMapSize(int *size);

private:
    QGLShaderProgram m_vertexProgram;
    GLuint *m_textures;

    QTerrain    m_terrain;
    QCamera     m_camera;
    QFrustum    m_frustum;
    QNoLodQuad  m_noLodQuad;

    float m_CameraSpeed;
};

#endif // QTGLWINDOW_H






















