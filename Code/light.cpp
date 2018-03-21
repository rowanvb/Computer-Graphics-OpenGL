#include "light.h"

QVector3D Light::getPosition() const
{
    return position;
}

void Light::setPosition(const QVector3D &value)
{
    position = value;
}

void Light::setPosition(const float &x, const float &y, const float &z)
{
    position = QVector3D(x,y,z);
}

QVector3D Light::getColor() const
{
    return color;
}

void Light::setColor(const QVector3D &value)
{
    color = value;
}

Light::Light()
{

}
