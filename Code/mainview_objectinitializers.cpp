#include "mainview.h"

static std::string catmodel = ":/models/cat.obj";
static std::string spheremodel = ":/models/sphere.obj";
static std::string cubemodel = ":/models/cube.obj";

void MainView::initObjects(int numSpheres){
    numObjects = numSpheres;
    allocateBuffers(numSpheres);
    addPlane(VAO[0], VBO[0], _textures[0]);

    for (int i = 1; i < numSpheres; ++i){
        Object *o;
        std::string model;
        if (i % 2){
            model = catmodel;
        }
        else {
            model = spheremodel;
        }
        o = new Mesh(QString(model.c_str()), VAO[i], VBO[i], _textures[i]);

        objects->push_back(o);
        setTexture(QImage(":/textures/rug_logo.png"), o->getTexture());

        float x = ((float) rand() / (RAND_MAX)) * 20.f - 10.f; // position between -10 and 10;
        float y = ((float) rand() / (RAND_MAX)) * 50.f;
        float z = ((float) rand() / (RAND_MAX)) * 20.f - 10.f;

        o->setObjectID(MainView::resolveFileName(model) + "_" + QString::number(i+1));
        o->setTranslation(QVector3D(x, y, z));
        o->setOriginalPosition(QVector3D(x, y, z));
        o->setMaterial(Material({0.1f, 0.8f, 0.8f, 100.f}));
    }
}

void MainView::initObjects_2(){
    numObjects = 13;
    allocateBuffers(13);
    addPlane(VAO[0], VBO[0], _textures[0]);
    QVector3D cubeposs[4] = {
        QVector3D(5, 5, -5),
        QVector3D(5, 5, 5),
        QVector3D(-5, 5, 5),
        QVector3D(-5, 5, -5)
    };

    QVector3D sphereposs[4] = {
        QVector3D(5, 10, 0),
        QVector3D(0, 12, 5),
        QVector3D(-5, 10, 0),
        QVector3D(0, 13, -5)
    };
    // Cubes
    for (int i = 1; i<5; ++i){
        Object* obj = new Mesh(QString(cubemodel.c_str()), VAO[i], VBO[i], _textures[i]);
        objects->push_back(obj);
        obj->setGravitation(0.05f);
        obj->setRotationSpeed(0.1f);
        obj->setRestitution(0.4f);
        obj->setMaterial(Material({0.1f, 0.8f, 0.8f, 10.f}));
        obj->setObjectID("Cube_" + QString::number(i));
        obj->setOriginalPosition(cubeposs[i-1]);
        obj->setTranslation(cubeposs[i-1]);
        setTexture(QImage(":/textures/brickwork-texture.png"), obj->getTexture());
    }

    // Spheres
    for (int i = 5; i<9; ++i){
        Object* obj = new Mesh(QString(spheremodel.c_str()), VAO[i], VBO[i], _textures[i]);
        objects->push_back(obj);
        obj->setGravitation(0.04f);
        obj->setRotationSpeed(1.5f);
        obj->setRestitution(0.85f);
        obj->setMaterial(Material({0.1f, 0.8f, 0.2f, 100.f}));
        obj->setObjectID("Sphere_" + QString::number(i-4));
        obj->setOriginalPosition(sphereposs[i-5]);
        obj->setTranslation(sphereposs[i-5]);
        if (i % 2)
            setTexture(QImage(":/textures/bluegrid.png"), obj->getTexture());
        else
            setTexture(QImage(":/textures/earthmap1k.png"), obj->getTexture());
    }
    // Cats
    for (int i = 9; i < 13; ++i){
        Object* obj = new Mesh(QString(catmodel.c_str()), VAO[i], VBO[i], _textures[i]);
        objects->push_back(obj);
        obj->setGravitation(0.03f);
        obj->setRotationSpeed(0.1f);
        obj->setRestitution(0.4f);
        obj->setMaterial(Material({0.1f, 0.8f, 0.8f, 10.f}));
        obj->setObjectID("Cat_" + QString::number(i-8));
        obj->setOriginalPosition(cubeposs[i-9] + QVector3D(0, 1.7f, 0));
        obj->setTranslation(cubeposs[i-9] + QVector3D(0, 1.7f, 0));
        obj->setUserDefinedZero(1.7f);
        if (i % 2)
            setTexture(QImage(":/textures/cat_norm.png"), obj->getTexture());
        else
            setTexture(QImage(":/textures/cat_diff.png"), obj->getTexture());
    }
}
