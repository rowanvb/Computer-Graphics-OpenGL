#include "mainview.h"
#include "math.h"
#include <regex>

#include <QDateTime>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(1000.0/60.0);
    lights[0].setPosition(1000.f, 1000.f, 1000.f);
    lights[0].setColor({1.f, 1.f, 1.f});
    objects = new std::vector<Object*>();
    _listmodel = new ObjectListModel(objects);
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * It is used to clean up the VBO's and VAO's.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();
    glDeleteBuffers(numObjects, VBO);
    glDeleteVertexArrays(numObjects, VAO);
    glDeleteTextures(numObjects, _textures);
    free(VBO);
    free(VAO);
    free(_textures);
    qDebug() << "MainView destructor";
}

/**
 * @brief MainView::initBuffers
 *
 * Intializes buffers for all objects
 *
 */
void MainView::initBuffers(){
    for (Object *o : *objects){
        glBindVertexArray(o->getVAO());

        glBindBuffer(GL_ARRAY_BUFFER, o->getVBO());
        glBufferData(GL_ARRAY_BUFFER, o->getBufferObject().size() * sizeof(Vertex), o->getBufferObject().data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(12));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(24));

    }
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    initObjects_2();
    // Initialize buffers
    initBuffers();

    // Initialize transformation matrices
    updatePerspective();
    updateTransformation(false);
    updateViewMatrix();

    // Initialize shader program
    createShaderProgram();
}

void MainView::addPlane(GLuint VAO, GLuint VBO, GLuint texture){
    Object* surface = new Plane(VAO, VBO, texture);
    objects->push_back(surface);
    setTexture(QImage(":/textures/bluegrid.png"), surface->getTexture());
    surface->setGravitation(0);
    surface->setRotationSpeed(0);
    surface->setObjectID("<< surface >>");
    surface->setMaterial(Material({0.1f, 0.8f, 0.8f, 100.f}));
    surface->setScale(100);
}

void MainView::allocateBuffers(int size){
    VAO = (GLuint*) malloc(size * sizeof(GLuint));
    VBO = (GLuint*) malloc(size * sizeof(GLuint));
    _textures = (GLuint*) malloc(size * sizeof(GLuint));
    glGenVertexArrays(size, VAO);
    glGenBuffers(size, VBO);
    glGenTextures(size, _textures);
}

/**
 * @brief MainView::createShaderProgram
 *
 */
void MainView::createShaderProgram()
{
    // Create shader program
    shaderProgram[NORMAL].addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader_normal.glsl");
    shaderProgram[NORMAL].addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader_normal.glsl");

    shaderProgram[PHONG].addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader_phong.glsl");
    shaderProgram[PHONG].addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader_phong.glsl");

    shaderProgram[GOURAUD].addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader_gouraud.glsl");
    shaderProgram[GOURAUD].addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader_gouraud.glsl");

    for (ShaderProgram &p : shaderProgram){
        p.link();
        p.setUniformModel(p.uniformLocation("modelTransform"));
        p.setUniformView(p.uniformLocation("viewMatrix"));
        p.setUniformProjection(p.uniformLocation("projectionMatrix"));
        p.setUniformNormal(p.uniformLocation("normalMatrix"));
        p.setUniformLightPosition(p.uniformLocation("lightPosition"));
        p.setUniformLightColor(p.uniformLocation("lightColor"));
        p.setUniformMaterial(p.uniformLocation("material"));
        p.setUniformSampler(p.uniformLocation("samplerUniform"));
    }
}


/**
 * @brief MainView::setTexture using simple repeated wrapping and linear filtering
 * @param img
 * @param texturePtr
 */
void MainView::setTexture(const QImage &img, GLuint texturePtr)
{
    QVector<quint8> texture = imageToBytes(img);
    glBindTexture(GL_TEXTURE_2D, texturePtr);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    update();
}

// --- OpenGL drawing

void MainView::drawObjects() {
    for (Object *o : *objects) {
        glUniformMatrix4fv(activeShaderProgram().getUniformModel(), 1,  GL_FALSE, o->getTransformationMatrix().data());
        glUniformMatrix3fv(activeShaderProgram().getUniformNormal(), 1, GL_FALSE, o->getNormalMatrix().data());
        glUniform4f(activeShaderProgram().getUniformMaterial(), o->getMaterial().ka, o->getMaterial().kd, o->getMaterial().ks, o->getMaterial().n);
        glBindVertexArray(o->getVAO());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, o->getTexture());
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) o->getNumVertices());
    }
}

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    activeShaderProgram().bind();

    // Set projection & view matrix uniform
    glUniformMatrix4fv(activeShaderProgram().getUniformProjection(), 1,  GL_FALSE, _projectionMatrix.data());
    glUniformMatrix4fv(activeShaderProgram().getUniformView(), 1,  GL_FALSE, _viewMatrix.data());

    // Set Light uniforms
    glUniform3f(activeShaderProgram().getUniformLightPosition(), lights[0].getPosition().x(), lights[0].getPosition().y(), lights[0].getPosition().z());
    glUniform3f(activeShaderProgram().getUniformLightColor(), lights[0].getColor().x(), lights[0].getColor().y(), lights[0].getColor().z());

    // Update objects
    updateTransformation(true);

    // Draw objects
    drawObjects();
    activeShaderProgram().release();

    // Notify mainwindow
    emit objectsChanged();
}

void MainView::updateTransformation(bool updateVars){
    for (Object *o : *objects){
        o->transform(updateVars);
    }
}

void MainView::updatePerspective(){
    float aspect_ratio = static_cast<float>(width()) / static_cast<float>(height());
    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(60, aspect_ratio, 0.1f, 500);
}

void MainView::updateViewMatrix(){
    QMatrix4x4 cameraTransform;
    _viewMatrix.setToIdentity();
    cameraTransform.rotate(QQuaternion::fromEulerAngles(_viewRotX, -_viewRotY, 0.f));
    QVector3D cameraPosition = cameraTransform * QVector3D(0, 0, -_distance);
    QVector3D cameraUpPosition = cameraTransform * QVector3D(0, 1, 0);
    _viewMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpPosition);
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen.
 * Modifies the projection matrix to keep the view consistent.
 *
 * @param newWidth New width of the window
 * @param newHeight New height of the widow
 */
void MainView::resizeGL(int newWidth, int newHeight) 
{
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
    updatePerspective();
}


void MainView::loadFile(QString file){
    QImage img;
    qDebug() << "Loaded " << file;
    img.load(file);
    if (!img.isNull())
        setTexture(img, _selectedObject->getTexture());
}

void MainView::resetScene() {
    for (Object *o : *objects)
        o->reset();
}

// Extracts filename from path, e.g. ":/models/cat.obj" -> "Cat"
QString MainView::resolveFileName(const std::string &filepath)
{
    std::regex objname("([^\\/]+)(?:\\.obj)");
    QString name = "Mesh";
    std::string str = std::regex_replace(filepath, objname, "$1", std::regex_constants::format_no_copy);
    if (str.length() > 0){
        str[0] = toupper(str[0]);
        name = QString(str.c_str());
    }
    return name;
}

// --- Private helpers

ShaderProgram& MainView::activeShaderProgram(){
    return shaderProgram[_shadingMode];
}

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
