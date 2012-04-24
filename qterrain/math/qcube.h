#ifndef QCUBE_H
#define QCUBE_H

#include <QVector3D>

/*!
    Class Cube
    two point can only define a cube.
*/
class QCube
{
public:
    QVector3D pos0;
    QVector3D pos1;

    QCube() {}
    QCube(float _x0, float _y0, float _z0, float _x1, float _y1, float _z1);
    QCube(const QCube& src);
    QCube(const QVector3D& _pos0, const QVector3D& _pos1);
    QCube(float _xSize, float _ySize, float _zSize);
    QCube(const QVector3D& pos, float _xSize, float _ySize, float _zSize);
    QCube(const QVector3D& size);

    void set(const QCube& v);
    void set(float _x0, float _y0, float _z0, float _x1, float _y1, float _z1);
    void setSize(const QVector3D& size);
    void setPos(const QVector3D& pos);
    QVector3D size() const;

private:
    virtual void update() {}
};

#endif // QCUBE_H
