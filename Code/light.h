#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>

class Light
{
    QVector3D position;
    QVector3D color;

public:
    Light();

    QVector3D getPosition() const;
    void setPosition(const QVector3D &value);
    void setPosition(const float &x, const float &y, const float &z);

    QVector3D getColor() const;
    void setColor(const QVector3D &value);
};

#endif // LIGHT_H
