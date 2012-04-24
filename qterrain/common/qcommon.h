#ifndef QCOMMON_H
#define QCOMMON_H

#include "math/qrect3dex.h"
#include "math/qcubeex.h"
#include "math/qplane3d.h"

#include <QMatrix4x4>

#include "qmath.h"

#define QEPSILON            (0.01f)
#define QPI                 3.14159265358979323846

#define WIDTH               854
#define HEIGHT              480

#define safe_delete(p)          { if(p) { delete (p);   (p) = 0; } }
#define safe_delete_array(p)    { if(p) { delete[] (p); (p) = 0; } }


//矩形是否与平面相切或在平面上，矩阵是否在平面法线的正方向上
inline bool QtPlane3DTestRect3D(const QPlane3D& plane, const QRect3D& rect)
{
    if((plane.getDistance(rect.pos0) > 0.0f) ||
            (plane.getDistance(rect.pos1) > 0.0f) ||
            (plane.getDistance(QVector3D(rect.pos0.x(), rect.pos1.y(), rect.pos1.z())) > 0.0f) ||
            (plane.getDistance(QVector3D(rect.pos1.x(), rect.pos0.y(), rect.pos1.z())) > 0.0f))
    {
        return true;
    }
    return false;
}

//测试立方体是否在平面法线的正方向上
inline bool QtPlane3DTestCube(const QPlane3D& plane, const QCube& cube)
{
    if(     (plane.getDistance(cube.pos0) > 0.0f) ||
            (plane.getDistance(cube.pos1) > 0.0f) ||
            (plane.getDistance(QVector3D(cube.pos0.x(), cube.pos1.y(), cube.pos0.z())) > 0.0f) ||
            (plane.getDistance(QVector3D(cube.pos0.x(), cube.pos1.y(), cube.pos1.z())) > 0.0f) ||
            (plane.getDistance(QVector3D(cube.pos1.x(), cube.pos0.y(), cube.pos1.z())) > 0.0f) ||
            (plane.getDistance(QVector3D(cube.pos1.x(), cube.pos0.y(), cube.pos0.z())) > 0.0f) ||
            (plane.getDistance(QVector3D(cube.pos0.x(), cube.pos0.y(), cube.pos1.z())) > 0.0f) ||
            (plane.getDistance(QVector3D(cube.pos1.x(), cube.pos1.y(), cube.pos0.z())) > 0.0f))
    {
        return true;
    }
    return false;
}

//测试的改进
inline bool QtPlane3DTestRect3DEx(const QPlane3D &plane, const QRect3DEx &rect)
{
    float dCenter = plane.getDistance(rect.center);

    if(dCenter >= 0)    return true;

    dCenter = fabs(dCenter);

    if(     fabs(plane.normal.x() * rect.normal0.x() + plane.normal.y() * rect.normal0.y() +
                 plane.normal.z() * rect.normal0.z()) > dCenter ||
            fabs(plane.normal.x() * rect.normal1.x() + plane.normal.y() * rect.normal1.y() +
                 plane.normal.z() * rect.normal1.z()) > dCenter)
    {
        return true;
    }
    return false;
}

//立方体测试的改进
inline bool QtPlane3DTestCubeEx(const QPlane3D &plane, const QCubeEx &cube)
{
    float dCenter = plane.getDistance(cube.center);

    if(dCenter >= 0)    return true;

    dCenter = fabs(dCenter);

    if(     fabs(plane.normal.x() * cube.normal0.x() + plane.normal.y() * cube.normal0.y() +
                 plane.normal.z() * cube.normal0.z()) > dCenter ||
            fabs(plane.normal.x() * cube.normal1.x() + plane.normal.y() * cube.normal1.y() +
                 plane.normal.z() * cube.normal1.z()) > dCenter ||
            fabs(plane.normal.x() * cube.normal2.x() + plane.normal.y() * cube.normal2.y() +
                 plane.normal.z() * cube.normal2.z()) > dCenter ||
            fabs(plane.normal.x() * cube.normal3.x() + plane.normal.y() * cube.normal3.y() +
                 plane.normal.z() * cube.normal3.z()) > dCenter)
    {
        return true;
    }
    return false;
}

//窗口点转近投影面
inline QVector2D QtClientToView(int x, int y, int width, int height, QMatrix4x4 &projMatrix)
{
    float px = 0.0f;
    float py = 0.0f;

    px = (((2.0f * x) / width) - 1.0f) / projMatrix(0, 0);
    py = (((-2.0f * y) / height + 1.0f) / projMatrix(1, 1));

    return QVector2D(px, py);
}

//判断点是否在平截头体内(CVV空间)
inline bool QtTestPointInCVV(const QMatrix4x4& viewProj, const QVector3D& pt)
{
    static float x, y, z, w;

    w = viewProj(0, 3) * pt.x() + viewProj(1, 3) * pt.y() + viewProj(2, 3) * pt.z() + viewProj(3, 3);

    x = viewProj(0, 0) * pt.x() + viewProj(1, 0) * pt.y() + viewProj(2, 0) * pt.z() + viewProj(3, 0);
    x = x / w;
    if(x > 1.0f || x < -1.0f)   return false;

    y = viewProj(0, 1) * pt.x() + viewProj(1, 1) * pt.y() + viewProj(2, 1) * pt.z() + viewProj(3, 1);
    y = y / w;
    if(y > 1.0f || y < 0.0f)    return false;

    z = viewProj(0, 2) * pt.x() + viewProj(1, 2) * pt.y() + viewProj(2, 2) * pt.z() + viewProj(3, 2);
    z = z / w;
    if(z > 1.0f || z < 0.0f)    return false;

    return true;
}

#endif // QCOMMON_H
