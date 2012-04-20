#ifndef QRECT3D_H
#define QRECT3D_H

#include <QVector2D>
#include <QVector3D>

class QRect3D
{
public:
    QVector3D pos0;
    QVector3D pos1;

    QRect3D() {}
    QRect3D(float _x0, float _x1, float _y0, float _y1, float _z);
    QRect3D(const QVector2D& _pos0, const QVector2D& _pos1, float _z);
    QRect3D(const QRect3D& rect);
    QRect3D(float _xSize, float _ySize);
    QRect3D(const QVector3D& pos, float _xSize, float _ySize);
    QRect3D(const QVector2D& size);

    void set(const QRect3D& rect);
    void set(float _x0, float _x1, float _y0, float _y1, float _z);
    void setSize(float _xSize, float _ySize);
    void setSize(const QVector2D& size);
    void setPos(const QVector3D& pos);
    QVector2D size() const;

private:
    virtual void update() {}
};

#endif // QRECT3D_H
