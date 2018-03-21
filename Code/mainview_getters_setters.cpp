#include "mainview.h"

ObjectListModel *MainView::listmodel() const
{
    return _listmodel;
}

Object *MainView::selectedObject() const
{
    return _selectedObject;
}

void MainView::setSelectedObject(int idx)
{
    _selectedObject = objects->at(idx);
}

/**
 * @brief MainView::setRotation
 *
 * Computes the transform matrix given the desired rotation around the x, y and z axis.
 *
 * @param rotateX Desired rotation around the x axis in degrees.
 * @param rotateY Desired rotation around the y axis in degrees.
 * @param rotateZ Desired rotation around the z axis in degrees.
 */
void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    if (_selectedObject)
        _selectedObject->setRotationVector({ static_cast<float>(rotateX), static_cast<float>(rotateY), static_cast<float>(rotateZ) });
    //_rotation = { static_cast<float>(rotateX), static_cast<float>(rotateY), static_cast<float>(rotateZ) };
    updateTransformation(false);
}

void MainView::setViewRotation(int x, int y){
    _viewRotX = x;
    _viewRotY = y;
    updateViewMatrix();
}

void MainView::setColor(int red, int green, int blue){
    QVector3D colors = QVector3D(red, green, blue);
    lights[0].setColor(colors / 255);
    update();
}

void MainView::setLightPosition(int x, int y, int z)
{
    lights[0].setPosition(x, y, z);
    update();
}

/**
 * @brief MainView::setScale
 *
 * Computers the transform matrix given the desired scale of the objects
 *
 * @param scale Desired scale factor
 */
void MainView::setScale(int scale)
{
    qDebug() << "Scale changed to " << scale;
    _scale = (float)scale/100;
    updateTransformation(false);
}

/**
 * @brief MainView::setShadingMode
 *
 * Unused function for setting the shading method
 *
 * @param shading Desired shading method
 */
void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    _shadingMode = shading;
}

float MainView::distance() const
{
    return _distance;
}

void MainView::setDistance(float distance)
{
    if (distance >= 0.f) // positive distance to center
        _distance = distance;
    updateViewMatrix();
}

float MainView::viewRotX() const
{
    return _viewRotX;
}

float MainView::viewRotY() const
{
    return _viewRotY;
}
