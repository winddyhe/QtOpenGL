#ifndef QRECT3DEX_H
#define QRECT3DEX_H

#include "qrect3d.h"

/*add rect center and two diagonal vector*/
class QRect3DEx : public QRect3D
{
public:
    QRect3DEx() {}
    QRect3DEx(float _x0, float _x1, float _y0, float _y1, float _z);
    QRect3DEx(const QVector2D& _pos0, const QVector2D& _pos1, float _z);
    QRect3DEx(const QRect3D& rect);
    QRect3DEx(float _xSize, float _ySize);
    QRect3DEx(const QVector3D& pos, float _xSize, float _ySize);
    QRect3DEx(const QVector2D& size);

public:
    QVector3D center;
    QVector3D normal0;
    QVector3D normal1;

private:
    void update();
};


#endif // QRECT3DEX_H
