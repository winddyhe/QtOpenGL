#ifndef QEBTIMEWHEEL_H
#define QEBTIMEWHEEL_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QGLShaderProgram>
#include <QVector3D>
#include <QVector2D>
#include <qmath.h>

struct ebTimeWheelVertex
{
    QVector3D position;
    QVector2D texCoord;
};

class QEBTimeWheel : public QObject
{
    Q_OBJECT
public:
    explicit QEBTimeWheel(QObject *parent = 0);
    virtual ~QEBTimeWheel();

    void drawTimeWheel(QGLShaderProgram &program, GLuint tex);

    void initTimeWheelDatas(int width, int height, int faceNums);

private:
    int m_iTime;

    int m_iIndicesNum;

    GLuint   *m_pVboIds;
};

#endif // QEBTIMEWHEEL_H
