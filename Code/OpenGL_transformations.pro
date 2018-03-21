#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T12:26:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL_transformations
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    mainview.cpp \
    user_input.cpp \
    model.cpp \
    object.cpp \
    sphere.cpp \
    cube.cpp \
    pyramid.cpp \
    mesh.cpp \
    shaderprogram.cpp \
    light.cpp \
    utility.cpp \
    objectlistmodel.cpp \
    mainview_getters_setters.cpp \
    plane.cpp \
    mainview_objectinitializers.cpp

HEADERS  += mainwindow.h \
    mainview.h \
    model.h \
    vertex.h \
    object.h \
    sphere.h \
    cube.h \
    pyramid.h \
    mesh.h \
    shaderprogram.h \
    light.h \
    material.h \
    objectlistmodel.h \
    plane.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
