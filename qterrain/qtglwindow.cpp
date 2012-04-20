#include "qtglwindow.h"

#include "mem/dbg.h"

QtGLWindow::QtGLWindow(QWidget *parent) :
    QGLWidget(parent),
    m_vertexProgram(context())
{
    startTimer(1000.0f / 70);
}

QtGLWindow::~QtGLWindow()
{
    m_vertexProgram.deleteLater();

    safe_delete_array(m_textures);
}

void QtGLWindow::useCurrentProgram(QGLShaderProgram &program)
{
    program.bind();
}

void QtGLWindow::initializeGL()
{
    initTextures();
    initShaders(m_vertexProgram, ":/shaders/vshader.vsh", ":/shaders/fshader.fsh");

    useCurrentProgram(m_vertexProgram);

    float fov = QPI * 0.25f;
    float aspect = (float)WIDTH / (float)HEIGHT;
    float nearPlane = 1.0f;
    float farPlane = 20000.0f;

    QVector3D position(0.0f, 300.0f, 0.0f);

    m_camera.setProjectionMatrix(fov, aspect, nearPlane, farPlane);
    m_camera.setPosition(position);

    const int mapSize = 128;
    const float w = mapSize * 16.0f;
    const float y = 1600.0f;

    QCubeEx world(QVector3D(-w, -y+300, -w),
                  QVector3D( w,  y+300,  w));

    m_terrain.create(&m_vertexProgram, m_textures[grassIndex],
                     mapSize, ":/images/heightmap128x128.png", world);
    qDebug() << "Terrain initialize..";
    m_noLodQuad.init(&m_terrain, m_frustum);
    qDebug() << "Lod initialize..";
    m_terrain.setLodType(&m_noLodQuad);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    qDebug() << "InitGL completed...";
}

void QtGLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    m_vertexProgram.setUniformValue("u_mvpMatrix", m_camera.getProjectionMatrix());

    qDebug() << "width=" << w << ", height=" << h;
    qDebug() << "ResizeGL Completed..";
}

void QtGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    m_camera.update(&m_frustum);
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(0, -300, 0);
    modelMatrix.rotate(-80, 1.0f, 0.0f, 0.0f);
    m_vertexProgram.setUniformValue("u_mvpMatrix", m_camera.getProjectionMatrix() * modelMatrix);

    m_terrain.render(m_frustum);
}

void QtGLWindow::initShaders(QGLShaderProgram &program, QString vshaderPath, QString fshaderPath)
{
    setlocale(LC_NUMERIC, "C");
    program.addShaderFromSourceFile(QGLShader::Vertex, vshaderPath);
    program.addShaderFromSourceFile(QGLShader::Fragment, fshaderPath);
    program.link();
    setlocale(LC_ALL, "");
}

void QtGLWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    updateGL();
}

void QtGLWindow::initTextures()
{
    m_textures = new GLuint[textureCount];

    for(int i = 0; i < textureCount; i++)
    {
        m_textures[i] = loadTexture(imagesPath[i]);
    }
}

GLuint QtGLWindow::loadTexture(QString texPath)
{
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    tex = bindTexture(QImage(texPath));
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    return tex;
}
