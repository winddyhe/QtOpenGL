#include "qrect3d.h"

/*QRect3D*/
QRect3D::QRect3D(const QRect3D &rect)
{
    pos0 = rect.pos0;
    pos1 = rect.pos1;
    update();
}

QRect3D::QRect3D(float _x0, float _x1, float _y0, float _y1, float _z)
{
    pos0 = QVector3D(_x0, _y0, _z);
    pos1 = QVector3D(_x1, _y1, _z);
    update();
}

QRect3D::QRect3D(const QVector2D &_pos0, const QVector2D &_pos1, float _z)
{
    pos0 = QVector3D(_pos0.x(), _pos0.y(), _z);
    pos1 = QVector3D(_pos1.x(), _pos1.y(), _z);
    update();
}

QRect3D::QRect3D(float _xSize, float _ySize)
{
    pos0 = QVector3D(0.0f, 0.0f, 0.0f);
    pos1 = QVector3D(_xSize, _ySize, 0.0f);
    update();
}

QRect3D::QRect3D(const QVector3D &pos, float _xSize, float _ySize)
{
    pos0 = pos;
    pos1 = QVector3D(pos0.x() + _xSize, pos0.y() + _ySize, pos0.z());
    update();
}

QRect3D::QRect3D(const QVector2D &size)
{
    pos0 = QVector3D(0.0f, 0.0f, 0.0f);
    pos1 = QVector3D(size.x(), size.y(), 0.0f);
    update();
}

void QRect3D::set(const QRect3D &rect)
{
    pos0 = rect.pos0;
    pos1 = rect.pos1;
    update();
}

void QRect3D::set(float _x0, float _x1, float _y0, float _y1, float _z)
{
    pos0 = QVector3D(_x0, _y0, _z);
    pos1 = QVector3D(_x1, _y1, _z);
    update();
}

void QRect3D::setSize(const QVector2D &size)
{
    pos1.setX(size.x());
    pos1.setY(size.y());
    update();
}

void QRect3D::setPos(const QVector3D &pos)
{
    pos1 = pos1 - pos0 + pos;
    pos0 = pos;
    update();
}

QVector2D QRect3D::size() const
{
    return QVector2D(pos1 - pos0);
}
