#ifndef QCAMERA_H
#define QCAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

#include "common/qcommon.h"
#include "common/qfrustum.h"

/*Camera Class*/
class QCamera
{
public:
    QCamera();
    ~QCamera();

    void setProjectionMatrix(float fov, float aspect, float near, float far);

    QMatrix4x4 getViewMatrix();
    QMatrix4x4 getProjectionMatrix();
    QMatrix4x4 getViewProjMatrix();

    QVector3D  getPosition();
    void setPosition(const QVector3D& pos);

    void strafe(float units);
    void walk(float units);
    void fly(float units);

    void pitch(float angle);
    void yaw(float angle);
    void roll(float angle);

    void update(QFrustum* frus = NULL);

protected:
    QVector3D       m_pos;
    QVector3D       m_look;
    QVector3D       m_up;
    QVector3D       m_right;

    QMatrix4x4      m_viewMatrix;
    QMatrix4x4      m_projMatrix;

    float           m_aspect;
    float           m_farPlane;
    float           m_nearPlane;
    float           m_fov;
};

#endif // QCAMERA_H
