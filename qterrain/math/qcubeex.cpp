#include "qcubeex.h"


QCubeEx::QCubeEx(const QCube &src) :
    QCube(src) {}
QCubeEx::QCubeEx(const QVector3D &pos, float _xSize, float _ySize, float _zSize) :
    QCube(pos, _xSize, _ySize, _zSize) {}
QCubeEx::QCubeEx(const QVector3D &size) :
    QCube(size) {}
QCubeEx::QCubeEx(const QVector3D &_pos0, const QVector3D &_pos1) :
    QCube(_pos0, _pos1) {}
QCubeEx::QCubeEx(float _x0, float _y0, float _z0, float _x1, float _y1, float _z1) :
    QCube(_x0, _y0, _z0, _x1, _y1, _z1) {}
QCubeEx::QCubeEx(float _xSize, float _ySize, float _zSize) :
    QCube(_xSize, _ySize, _zSize) {}

void QCubeEx::update()
{
    center = (pos1 - pos0) / 2.0f + pos0;
    normal0 = pos1 - center;
    normal1 = QVector3D(pos1.x(), pos0.y(), pos1.z()) - center;
    normal2 = QVector3D(pos0.x(), pos0.y(), pos1.z()) - center;
    normal3 = QVector3D(pos0.x(), pos1.y(), pos1.z()) - center;
}
