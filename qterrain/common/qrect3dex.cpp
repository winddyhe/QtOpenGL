#include "qrect3dex.h"

/*QRect3DEx*/
QRect3DEx::QRect3DEx(const QRect3D &rect) :
    QRect3D(rect) {}

QRect3DEx::QRect3DEx(const QVector2D &size) :
    QRect3D(size) {}

QRect3DEx::QRect3DEx(const QVector2D &_pos0, const QVector2D &_pos1, float _z) :
    QRect3D(_pos0, _pos1, _z) {}

QRect3DEx::QRect3DEx(const QVector3D &pos, float _xSize, float _ySize) :
    QRect3D(pos, _xSize, _ySize) {}

QRect3DEx::QRect3DEx(float _x0, float _x1, float _y0, float _y1, float _z) :
    QRect3D(_x0, _x1, _y0, _y1, _z) {}

QRect3DEx::QRect3DEx(float _xSize, float _ySize) :
    QRect3D(_xSize, _ySize) {}

void QRect3DEx::update()
{
    center = (pos1 - pos0) / 2.0f + pos0;
    normal0 = pos1 - center;
    normal1 = QVector3D(pos1.x(), pos0.y(), pos0.z()) - center;
}
