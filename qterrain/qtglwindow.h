#ifndef QTGLWINDOW_H
#define QTGLWINDOW_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QBasicTimer>

#include "common/qcommon.h"

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

private:
    void initTextures();
    GLuint loadTexture(QString texPath);
    void initShaders(QGLShaderProgram& program, QString vertexPath, QString fragmentPath);
    void useCurrentProgram(QGLShaderProgram& program);

private:
    QGLShaderProgram*   m_program;
    QMatrix4x4          m_projectionMatrix;
    GLuint*             m_textures;
};

#endif // QTGLWINDOW_H
