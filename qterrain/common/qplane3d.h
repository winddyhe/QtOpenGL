#ifndef QPLANE3D_H
#define QPLANE3D_H

#include <QVector3D>

#include <qmath.h>

class QPlane3D
{
public:
    QPlane3D();
    QPlane3D(QVector3D _normal, float _d);
    QPlane3D(float _a, float _b, float _c, float _d);
    QPlane3D(const QPlane3D& plane);

    void set(QVector3D _normal, float _d);
    void set(float _a, float _b, float _c, float _d);
    void setNormal(const QVector3D& _normal);
    void setD(float _d);

    float getDistance(const QVector3D& point) const;

    void normalize();
    QVector3D projectPointToPlane(const QVector3D& point) const;

public:
    float d;
    QVector3D normal;
};

#endif // QPLANE3D_H
