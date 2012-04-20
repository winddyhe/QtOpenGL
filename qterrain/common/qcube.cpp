#include "qcube.h"

QCube::QCube(float _x0, float _y0, float _z0, float _x1, float _y1, float _z1)
{
   pos0 = QVector3D(_x0, _y0, _z0);
   pos1 = QVector3D(_x1, _y1, _z1);
   update();
}

QCube::QCube(const QCube &src)
{
    pos0 = src.pos0;
    pos1 = src.pos1;
    update();
}

QCube::QCube(const QVector3D &_pos0, const QVector3D &_pos1)
{
    pos0 = _pos0;
    pos1 = _pos1;
    update();
}

QCube::QCube(float _xSize, float _ySize, float _zSize)
{
    pos0 = QVector3D(0.0f, 0.0f, 0.0f);
    pos1 = QVector3D(_xSize, _ySize, _zSize);
    update();
}

QCube::QCube(const QVector3D &pos, float _xSize, float _ySize, float _zSize)
{
    pos0 = pos;
    pos1 = pos0 + QVector3D(_xSize, _ySize, _zSize);
    update();
}

QCube::QCube(const QVector3D &size)
{
    pos0 = QVector3D(0.0f, 0.0f, 0.0f);
    pos1 = size;
    update();
}

void QCube::set(const QCube &v)
{
    pos0 = v.pos0;
    pos1 = v.pos1;
    update();
}

void QCube::set(float _x0, float _y0, float _z0, float _x1, float _y1, float _z1)
{
    pos0 = QVector3D(_x0, _y0, _z0);
    pos1 = QVector3D(_x1, _y1, _z1);
    update();
}

void QCube::setSize(const QVector3D &size)
{
    pos1 = pos0 + size;
    update();
}

void QCube::setPos(const QVector3D &pos)
{
    pos1 = pos1 - pos0 + pos;
    pos0 = pos;
    update();
}

QVector3D QCube::size() const
{
    return (pos1 - pos0);
}
