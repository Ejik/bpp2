#-------------------------------------------------
#
# Project created by QtCreator 2013-01-01T17:31:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bpp2
TEMPLATE = app

# The application version
VERSION = 2.0.0.19

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

SOURCES += main.cpp\
        mainwindow.cpp \
    aboutview.cpp \
    acotcore.cpp \
    importer.cpp

HEADERS  += mainwindow.h \
    aboutview.h \
    acotcore.h \
    importer.h

FORMS    += mainwindow.ui \
    aboutview.ui

RESOURCES += \
    bppax.qrc

OTHER_FILES += \
      bppax.rc

#RC_FILE = bppax.rc
