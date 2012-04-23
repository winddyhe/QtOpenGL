#ifndef QTGAMEWINDOW_H
#define QTGAMEWINDOW_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QMatrix4x4>

#include "geometryengine.h"
#include "qebtimewheel.h"

class QtGameWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit QtGameWindow(QWidget *parent = 0);
    virtual ~QtGameWindow();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void timerEvent(QTimerEvent *e);

    void onUpdate(float delta);
    void onRender();

    void initShader();
    void initTexture();
    void drawRectByFan(GLuint tex, GLfloat depth, QGLShaderProgram &program, float centerX, float centerY);

protected:
    QGLShaderProgram    m_program;

    QMatrix4x4  m_projection;
    QMatrix4x4  m_modelView;

    GLint m_positionLoc;
    GLint m_colorLoc;
    GLint m_modelViewLoc;
    GLint m_projectionLoc;

    GLint m_texture;

    GeometryEngine *m_geometries;

    QEBTimeWheel *m_timeWheel;

    int m_rot;
};

#endif // QTGAMEWINDOW_H



































