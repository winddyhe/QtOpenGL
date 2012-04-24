#include "qplane3d.h"

/*QPlane3D*/
QPlane3D::QPlane3D()
{
    normal = QVector3D(0.0f, 0.0f, 0.0f);
    d = 0.0f;
}

QPlane3D::QPlane3D(const QPlane3D &plane)
{
    normal = plane.normal;
    d = plane.d;
}

QPlane3D::QPlane3D(QVector3D _normal, float _d)
{
    normal = _normal;
    d = _d;
}

QPlane3D::QPlane3D(float _a, float _b, float _c, float _d)
{
    normal = QVector3D(_a, _b, _c);
    d = _d;
}

void QPlane3D::set(QVector3D _normal, float _d)
{
    normal = _normal;
    d = _d;
}

void QPlane3D::set(float _a, float _b, float _c, float _d)
{
    normal = QVector3D(_a, _b, _c);
    d = _d;
}

void QPlane3D::setNormal(const QVector3D &_normal)
{
    normal = _normal;
}

void QPlane3D::setD(float _d)
{
    d = _d;
}

//error may be in here
void QPlane3D::normalize()
{
    float dis = normal.length();
    if(normal.x() < 0)   //a的正负
    {
        dis = dis * (-1);
    }
    normal.normalize();
    this->d = d / dis;
}

float QPlane3D::getDistance(const QVector3D& point) const
{
    float dis = ((normal.x() * point.x() + normal.y() * point.y() + normal.z() * point.z()) + d) /
            (normal.length());
    return dis;
}

QVector3D QPlane3D::projectPointToPlane(const QVector3D &point) const
{
    float fd = getDistance(point);

    return QVector3D(point - normal * fd);
}
