#ifndef MAINVIEW_H
#define MAINVIEW_H


#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <QAbstractListModel>
#include <memory>

#include "model.h"
#include "vertex.h"
#include "sphere.h"
#include "cube.h"
#include "pyramid.h"
#include "plane.h"
#include "mesh.h"
#include "shaderprogram.h"
#include "light.h"
#include "material.h"
#include "objectlistmodel.h"

#define PI 3.14159265

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    QMatrix4x4 _projectionMatrix;
    QVector3D _rotation;
    QMatrix3x3 _normalMatrix;
    float _scale = 1.f;
    GLuint _shadingMode = PHONG;
    ObjectListModel *_listmodel;
    Object* _selectedObject = NULL;

    //Camera position
    float _distance = 10.f;
    QVector3D _eye = QVector3D(0, 0, -10.f);
    QMatrix4x4 _viewMatrix;
    float _viewRotX = 0, _viewRotY = 0;

    // Object related params
    GLuint *VAO;
    GLuint *VBO;
    GLuint* _textures;
    std::vector<Object*> *objects;
    int numObjects = 100;
    Light lights[1];
    ShaderProgram shaderProgram[3];

    QPoint dragStartPosition; // Position used for mouse dragging

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);
    void setColor(int red, int green, int blue);
    void setLightPosition(int x, int y, int z);
    void loadFile(QString file);
    void setViewRotation(int x, int y);
    void setSelectedObject(int idx);
    void setDistance(float distance);
    void resetScene();

    float distance() const;

    ObjectListModel *listmodel() const;
    Object *selectedObject() const;

    static QString resolveFileName(const std::string &filepath);

    float viewRotX() const;
    float viewRotY() const;

signals:
    void objectsChanged();

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

private:
    void createShaderProgram();
    void initBuffers();
    void allocateBuffers(int size);
    void initObjects(int numObjects);
    void initObjects_2();
    void addPlane(GLuint VAO, GLuint VBO, GLuint texture);

    void updateTransformation(bool updateVars);
    void updatePerspective();
    void updateViewMatrix();
    void drawObjects();

    void setTexture(const QImage &file, GLuint texture);
    QVector<quint8> imageToBytes(QImage image);
    ShaderProgram& activeShaderProgram();
};

#endif // MAINVIEW_H
