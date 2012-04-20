#ifndef QCUBEEX_H
#define QCUBEEX_H

#include "qcube.h"

/*!
    QCubeEx Class
    addition 4 dialgonal vector, and the center point of cube
*/
class QCubeEx : public QCube
{
public:
    QCubeEx() {}
    QCubeEx(float _x0, float _y0, float _z0, float _x1, float _y1, float _z1);
    QCubeEx(const QCube& src);
    QCubeEx(const QVector3D& _pos0, const QVector3D& _pos1);
    QCubeEx(float _xSize, float _ySize, float _zSize);
    QCubeEx(const QVector3D& pos, float _xSize, float _ySize, float _zSize);
    QCubeEx(const QVector3D& size);

    QVector3D center;
    QVector3D normal0;
    QVector3D normal1;
    QVector3D normal2;
    QVector3D normal3;

private:
    void update();
};


#endif // QCUBEEX_H
