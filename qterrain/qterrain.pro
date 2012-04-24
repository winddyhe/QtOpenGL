
QT      += opengl gui

SOURCES += main.cpp \
    math/qrect3dex.cpp \
    math/qrect3d.cpp \
    math/qplane3d.cpp \
    math/qfrustum.cpp \
    math/qcubeex.cpp \
    math/qcube.cpp \
    mem/dbg.cpp \
    qtglwindow.cpp \
    scene/qterrain.cpp \
    scene/qlod.cpp \
    scene/qnolodquad.cpp
HEADERS += \
    common/qcommon.h \
    math/qrect3d.h \
    math/qplane3d.h \
    math/qfrustum.h \
    math/qcubeex.h \
    math/qcube.h \
    math/qrect3dex.h \
    mem/dbg.h \
    qtglwindow.h \
    scene/qterrain.h \
    scene/qlod.h \
    scene/qnolodquad.h

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
    shaders/vertexshader.vsh \
    shaders/fragmentshader.fsh

RESOURCES += \
    images.qrc \
    shaders.qrc




















