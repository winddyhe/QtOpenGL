#include "qtglwindow.h"

QString ImagesPath[] = {
    ":/images/water.png",
    ":/images/cube.bmp",
    ":/images/grass2.jpg",
    ":/images/grass.png",
    ":/images/heightmap128x128.png",
    ":/images/landform.png",
};

enum ETextureIndex
{
    texWaterIndex,
    texCubeIndex,
    texGrass2Index,
    texGrassIndex,
    texHeightMap128x128Index,
    texLandformIndex,

    textureCount
};

QtGLWindow::QtGLWindow(QWidget *parent) :
    QGLWidget(parent)
{
    m_program = new QGLShaderProgram(context());
}

QtGLWindow::~QtGLWindow()
{
    m_program->deleteLater();

    for(int i = 0; i < textureCount; i++)
    {
        deleteTexture(m_textures[i]);
    }
}

void QtGLWindow::initializeGL()
{
    initTextures();
    initShaders(*m_program, ":/shaders/vertexshader.vsh", ":/shaders/fragmentshader.fsh");
    useCurrentProgram(*m_program);
}

void QtGLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    QMatrix4x4 matrix;
    matrix.setToIdentity();

    float fov = QPI * 0.25f;
    float aspect = (float)WIDTH / (float)HEIGHT;
    float near = 1.0f;
    float far = 2000.0f;

    matrix.perspective(fov, aspect, near, far);

    QMatrix4x4 m(1, 0, 0, 0,
                 0,-1, 0, 0,
                 0, 0,-1, 0,
                 0, 0, 0, 1);

    m_projectionMatrix = matrix * m;
}

void QtGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        m_textures[i] = loadTexture(ImagesPath[i]);
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

void QtGLWindow::initShaders(QGLShaderProgram& program, QString vertexPath, QString fragmentPath)
{
    setlocale(LC_NUMERIC, "C");
    program.addShaderFromSourceFile(QGLShader::Vertex, vertexPath);
    program.addShaderFromSourceFile(QGLShader::Fragment, fragmentPath);
    program.link();
    setlocale(LC_ALL, "");
}

void QtGLWindow::useCurrentProgram(QGLShaderProgram &program)
{
    program.bind();
}

