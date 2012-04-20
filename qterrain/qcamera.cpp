#include "qcamera.h"

QCamera::QCamera()
{
    m_pos = QVector3D(0.0f, 0.0f, 0.0f);

    m_right = QVector3D(1.0f, 0.0f, 0.0f);
    m_up = QVector3D(0.0f, 1.0f, 0.0f);
    m_look = QVector3D(0.0f, 0.0f, 1.0f);
}

QCamera::~QCamera()
{
}

void QCamera::setProjectionMatrix(float fov, float aspect, float near, float far)
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.perspective(fov, aspect, near, far);

    QMatrix4x4 m(1, 0, 0, 0,
                 0,-1, 0, 0,
                 0, 0,-1, 0,
                 0, 0, 0, 1);

    m_projMatrix = matrix * m;
}

QMatrix4x4 QCamera::getProjectionMatrix()
{
    return m_projMatrix;
}

QMatrix4x4 QCamera::getViewProjMatrix()
{
    return m_projMatrix * m_viewMatrix;
}

void QCamera::setPosition(const QVector3D &pos)
{
    m_right = QVector3D(1.0f, 0.0f, 0.0f);
    m_up = QVector3D(0.0f, 1.0f, 0.0f);
    m_look = QVector3D(0.0f, 0.0f, 1.0f);

    m_pos = pos;
}

QVector3D QCamera::getPosition()
{
    return m_pos;
}

void QCamera::strafe(float units)
{
    m_pos += m_right * units;
}

void QCamera::walk(float units)
{
    m_pos += m_look * units;
}

void QCamera::fly(float units)
{
    m_pos += m_up * units;
}

void QCamera::pitch(float angle)
{
    QMatrix4x4 T;
    T.setToIdentity();
    T.rotate(angle, m_right);

    m_up = m_up * T;
    m_look = m_look * T;
}

void QCamera::yaw(float angle)
{
    QMatrix4x4 T;
    T.setToIdentity();
    T.rotate(angle, m_up);

    m_look = m_look * T;
    m_right = m_right * T;
}

void QCamera::roll(float angle)
{
    QMatrix4x4 T;
    T.setToIdentity();
    T.rotate(angle, m_look);

    m_up = m_up * T;
    m_right = m_right * T;
}

QMatrix4x4 QCamera::getViewMatrix()
{
    m_look.normalize();
    m_up = QVector3D::crossProduct(m_look, m_right);
    m_up.normalize();

    m_right = QVector3D::crossProduct(m_up, m_look);
    m_right.normalize();

    float x = -QVector3D::dotProduct(m_right, m_pos);
    float y = -QVector3D::dotProduct(m_up, m_pos);
    float z = -QVector3D::dotProduct(m_look, m_pos);

//    qDebug() << "look=" << m_look << ", right=" << m_right << ", up=" << m_up;

    m_viewMatrix(0,0) = m_right.x();
    m_viewMatrix(1,0) = m_right.y();
    m_viewMatrix(2,0) = m_right.z();
    m_viewMatrix(3,0) = x;

    m_viewMatrix(0,1) = m_up.x();
    m_viewMatrix(1,1) = m_up.y();
    m_viewMatrix(2,1) = m_up.z();
    m_viewMatrix(3,1) = y;

    m_viewMatrix(0,2) = m_look.x();
    m_viewMatrix(1,2) = m_look.y();
    m_viewMatrix(2,2) = m_look.z();
    m_viewMatrix(3,2) = z;

    m_viewMatrix(0,3) = 0.0f;
    m_viewMatrix(1,3) = 0.0f;
    m_viewMatrix(2,3) = 0.0f;
    m_viewMatrix(3,3) = 1.0f;

    return m_viewMatrix;
}

void QCamera::update(QFrustum *frus)
{
    getViewMatrix();

    QMatrix4x4 viewProj = getViewProjMatrix();

//    qDebug() << "ViewProj=" << viewProj;

    //更新平截头体
    if(frus)
    {
//        qDebug() << "leftplane: normal=" << frus->leftPlane.normal << ", d=" << frus->leftPlane.d;
//        qDebug() << "rightplane: normal=" << frus->rightPlane.normal << ", d=" << frus->rightPlane.d;
//        qDebug() << "topplane: normal=" << frus->topPlane.normal << ", d=" << frus->topPlane.d;
//        qDebug() << "buttomplane: normal=" << frus->bottomPlane.normal << ", d=" << frus->bottomPlane.d;
//        qDebug() << "nearplane: normal=" << frus->nearPlane.normal << ", d=" << frus->nearPlane.d;
//        qDebug() << "farplane: normal=" << frus->farPlane.normal << ", d=" << frus->farPlane.d;
//        qDebug() << "before-------------------------------------";
        frus->extractFromMatrix(viewProj);
//        qDebug() << "after--------------------------------------";
//        qDebug() << "leftplane: normal=" << frus->leftPlane.normal << ", d=" << frus->leftPlane.d;
//        qDebug() << "rightplane: normal=" << frus->rightPlane.normal << ", d=" << frus->rightPlane.d;
//        qDebug() << "topplane: normal=" << frus->topPlane.normal << ", d=" << frus->topPlane.d;
//        qDebug() << "buttomplane: normal=" << frus->bottomPlane.normal << ", d=" << frus->bottomPlane.d;
//        qDebug() << "nearplane: normal=" << frus->nearPlane.normal << ", d=" << frus->nearPlane.d;
//        qDebug() << "farplane: normal=" << frus->farPlane.normal << ", d=" << frus->farPlane.d;
    }
}




























