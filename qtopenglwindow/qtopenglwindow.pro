# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

QT  += opengl gui

SOURCES += main.cpp \
    qtgamewindow.cpp \
    geometryengine.cpp \
    qterrain.cpp \
    qebtimewheel.cpp
HEADERS += \
    qtgamewindow.h \
    geometryengine.h \
    qterrain.h \
    qebtimewheel.h
FORMS +=

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    fshader.fsh \
    vshader.vsh

RESOURCES += \
    shaders.qrc \
    images.qrc




















