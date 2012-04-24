#ifndef QFRUSTUM_H
#define QFRUSTUM_H

#include <QMatrix4x4>
#include <QVector3D>

#include "qplane3d.h"
#include "qcubeex.h"
#include "qrect3dex.h"
#include "qrect3d.h"
#include "common/qcommon.h"

class QFrustum
{
public:
    QFrustum() {}

    //根据视图投影矩阵得到6个面的平截头体
    void extractFromMatrix(const QMatrix4x4& matrix, bool normalizePlanes = true);

    bool testPoint(const QVector3D& point) const;
    bool testRect3D(const QRect3D& rect) const;
    bool testCube(const QCube& cube) const;
    bool testRect3DEx(const QRect3D &rect) const;
    bool testCubeEx(const QCube &cube) const;
    bool testSphere(const QVector3D& pos, float r) const;

public:
    QPlane3D leftPlane;
    QPlane3D rightPlane;
    QPlane3D topPlane;
    QPlane3D bottomPlane;
    QPlane3D nearPlane;
    QPlane3D farPlane;

    QCubeEx m_bound;

    QVector3D m_vertices[8];
};

#endif // QFRUSTUM_H
