#include "qfrustum.h"

/*QFrustum*/
void QFrustum::extractFromMatrix(const QMatrix4x4 &matrix, bool normalizePlanes)
{
    leftPlane.normal.setX(matrix(0,3) + matrix(0, 0));
    leftPlane.normal.setY(matrix(1,3) + matrix(1, 0));
    leftPlane.normal.setZ(matrix(2,3) + matrix(2, 0));
    leftPlane.d = (matrix(3,3) + matrix(3, 0));

    rightPlane.normal.setX(matrix(0,3) - matrix(0, 0));
    rightPlane.normal.setY(matrix(1,3) - matrix(1, 0));
    rightPlane.normal.setZ(matrix(2,3) - matrix(2, 0));
    rightPlane.d = (matrix(3,3) - matrix(3, 0));

    topPlane.normal.setX(matrix(0,3) - matrix(0, 1));
    topPlane.normal.setY(matrix(1,3) - matrix(1, 1));
    topPlane.normal.setZ(matrix(2,3) - matrix(2, 1));
    topPlane.d = (matrix(3,3) - matrix(3, 1));

    bottomPlane.normal.setX(matrix(0,3) + matrix(0, 1));
    bottomPlane.normal.setY(matrix(1,3) + matrix(1, 1));
    bottomPlane.normal.setZ(matrix(2,3) + matrix(2, 1));
    bottomPlane.d = (matrix(3,3) + matrix(3, 1));

    nearPlane.normal.setX(matrix(0,2));
    nearPlane.normal.setY(matrix(1,2));
    nearPlane.normal.setZ(matrix(2,2));
    nearPlane.d = (matrix(3,2));

    farPlane.normal.setX(matrix(0,3) - matrix(0, 2));
    farPlane.normal.setY(matrix(1,3) - matrix(1, 2));
    farPlane.normal.setZ(matrix(2,3) - matrix(2, 2));
    farPlane.d = (matrix(3,3) - matrix(3, 2));

    if(normalizePlanes)
    {
        leftPlane.normalize();
        rightPlane.normalize();
        topPlane.normalize();
        bottomPlane.normalize();
        nearPlane.normalize();
        farPlane.normalize();
    }
}

bool QFrustum::testPoint(const QVector3D &point) const
{
    if(     leftPlane.getDistance(point)    < 0.0f  ||
            rightPlane.getDistance(point)   < 0.0f  ||
            topPlane.getDistance(point)     < 0.0f  ||
            bottomPlane.getDistance(point)  < 0.0f  ||
            nearPlane.getDistance(point)    < 0.0f  ||
            farPlane.getDistance(point)     < 0.0f)
    {
        return false;
    }
    return true;
}

bool QFrustum::testRect3D(const QRect3D &rect) const
{
    if(     !QtPlane3DTestRect3D(leftPlane, rect)   ||
            !QtPlane3DTestRect3D(rightPlane, rect)  ||
            !QtPlane3DTestRect3D(topPlane, rect)    ||
            !QtPlane3DTestRect3D(bottomPlane, rect) ||
            !QtPlane3DTestRect3D(nearPlane, rect)   ||
            !QtPlane3DTestRect3D(farPlane, rect))
    {
        return false;
    }
    return true;
}

bool QFrustum::testCube(const QCube &cube) const
{
    if(     !QtPlane3DTestCube(leftPlane, cube)   ||
            !QtPlane3DTestCube(rightPlane, cube)  ||
            !QtPlane3DTestCube(topPlane, cube)    ||
            !QtPlane3DTestCube(bottomPlane, cube) ||
            !QtPlane3DTestCube(nearPlane, cube)   ||
            !QtPlane3DTestCube(farPlane, cube))
    {
        return false;
    }
    return true;
}

bool QFrustum::testRect3DEx(const QRect3D &rect) const
{
    if(     !QtPlane3DTestRect3DEx(leftPlane, rect)   ||
            !QtPlane3DTestRect3DEx(rightPlane, rect)  ||
            !QtPlane3DTestRect3DEx(topPlane, rect)    ||
            !QtPlane3DTestRect3DEx(bottomPlane, rect) ||
            !QtPlane3DTestRect3DEx(nearPlane, rect)   ||
            !QtPlane3DTestRect3DEx(farPlane, rect))
    {
        return false;
    }
    return true;
}

bool QFrustum::testCubeEx(const QCube &cube) const
{
    if(     !QtPlane3DTestCubeEx(leftPlane, cube)   ||
            !QtPlane3DTestCubeEx(rightPlane, cube)  ||
            !QtPlane3DTestCubeEx(topPlane, cube)    ||
            !QtPlane3DTestCubeEx(bottomPlane, cube) ||
            !QtPlane3DTestCubeEx(nearPlane, cube)   ||
            !QtPlane3DTestCubeEx(farPlane, cube))
    {
        return false;
    }
    return true;
}

bool QFrustum::testSphere(const QVector3D &pos, float r) const
{
    if(     leftPlane.getDistance(pos)  + r < 0.0f  ||
            rightPlane.getDistance(pos) + r < 0.0f  ||
            topPlane.getDistance(pos)   + r < 0.0f  ||
            bottomPlane.getDistance(pos)+ r < 0.0f  ||
            nearPlane.getDistance(pos)  + r < 0.0f  ||
            farPlane.getDistance(pos)   + r < 0.0f)
    {
        return false;
    }
    return true;
}
