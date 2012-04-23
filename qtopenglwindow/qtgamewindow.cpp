#include "qtgamewindow.h"

QtGameWindow::QtGameWindow(QWidget *parent) :
    QGLWidget(parent)
{
    startTimer(1000.0f / 60);
    m_geometries = new GeometryEngine();
    m_timeWheel = NULL;
    m_rot = 10;
}

QtGameWindow::~QtGameWindow()
{
}

void QtGameWindow::initializeGL()
{
    qglClearColor(Qt::black);
    initShader();
    initTexture();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

//    m_geometries->init();
//    m_timeWheel = new QEBTimeWheel();
//    m_timeWheel->initTimeWheelDatas(60, 24, 6);
}

void QtGameWindow::paintGL()
{
    onUpdate(1);
    onRender();
}

void QtGameWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    float aspect = (float)w / ((float)h ? h : 1);

    m_projection.setToIdentity();
    m_projection.perspective(60.0f, aspect, 1.0f, 2000.0f);
}

void QtGameWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    updateGL();
    m_rot = m_rot + 1;
}

void QtGameWindow::onUpdate(float delta)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float aspect = (GLfloat)width() / (GLfloat)height();
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, aspect, 1.0f, 2000.0f);
}

void QtGameWindow::onRender()
{
    glViewport(0, 0, width(), height());
//    QMatrix4x4 modelView;
//    modelView.translate(0.0, 0.0, -200.0);
////    modelView.rotate(150.0 + m_rot, 1.0, 0.0, 1.0);

//    m_program.setUniformValue(m_projectionLoc, m_projection);
//    m_program.setUniformValue(m_modelViewLoc, modelView);

////    m_program.setUniformValue("texture", 0);
////    m_geometries->drawCubeGeometry(&m_program);
//    m_timeWheel->drawTimeWheel(m_program, m_texture);
    drawRectByFan(m_texture, -98.0f, m_program, 0.0f, 0.0f);
}

void QtGameWindow::initShader()
{
    setlocale(LC_NUMERIC, "C");

    if(!m_program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.vsh"))
        close();

    if(!m_program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.fsh"))
        close();

    if(!m_program.link())
        close();

    m_positionLoc = m_program.attributeLocation("a_position");
    m_colorLoc    = m_program.attributeLocation("a_color");

    m_modelViewLoc  = m_program.uniformLocation("u_modelViewMatrix");
    m_projectionLoc = m_program.uniformLocation("u_projectionMatrix");

    if(!m_program.bind())
        close();

    setlocale(LC_ALL, "");
}

void QtGameWindow::initTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    m_texture = bindTexture(QImage(":/images/cube1.bmp"));

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


void QtGameWindow::drawRectByFan(GLuint tex, GLfloat depth, QGLShaderProgram &program, float centerX, float centerY)
{
    QMatrix4x4 m;
    m.translate(0.0f, 0.0f, -500.0f);
    m.rotate(90, 1.0f, 0.0f, 0.0f);
    m_program.setUniformValue(m_projectionLoc, m_projection);
    m_program.setUniformValue(m_modelViewLoc, m);

    QVector2D center(centerX, centerY);

    int k = 100;

    QVector<QVector2D> vertices;
    vertices << center;
    vertices << center + QVector2D(-k, k);

    vertices << center + QVector2D( 0, k);

    vertices << center + QVector2D( k, k);

    vertices << center + QVector2D( k, 0);

    vertices << center + QVector2D( k, -k);

    vertices << center + QVector2D( 0, -k);
\
    vertices << center + QVector2D(-k, -k);

    vertices << center + QVector2D(-k, 0);

    vertices << center + QVector2D(-k, k);

    QVector<QVector2D> texCoord;
    texCoord << QVector2D(0.5f, 0.5f);
    texCoord << QVector2D(0.0f, 1.0f);
    texCoord << QVector2D(0.5f, 1.0f);
    texCoord << QVector2D(1.0f, 1.0f);
    texCoord << QVector2D(1.0f, 0.5f);
    texCoord << QVector2D(1.0f, 0.0f);
    texCoord << QVector2D(0.5f, 0.0f);
    texCoord << QVector2D(0.0f, 0.0f);
    texCoord << QVector2D(0.0f, 0.5f);
    texCoord << QVector2D(0.0f, 1.0f);

    float height[10] = {0};

    program.setUniformValue("u_startPos", QVector2D(10.0f, 10.0f));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    program.enableAttributeArray("a_position");
    program.enableAttributeArray("a_texcoord");
    program.enableAttributeArray("a_height");

    program.setUniformValue("u_texture", 0);
    program.setAttributeArray("a_position", vertices.constData());
    program.setAttributeArray("a_texcoord", texCoord.constData());
    program.setAttributeArray("a_height", height, 1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
}
