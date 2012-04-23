
QT      += opengl gui

SOURCES += main.cpp \
    scene/qnolod.cpp \
    scene/qterrain.cpp \
    mem/dbg.cpp \
    common/qbit.cpp \
    common/qcommon.cpp \
    common/qcube.cpp \
    common/qcubeex.cpp \
    common/qfrustum.cpp \
    common/qplane3d.cpp \
    common/qrect3d.cpp \
    common/qrect3dex.cpp \
    qcamera.cpp \
    qtglwindow.cpp

HEADERS += \
    scene/qnolod.h \
    scene/qterrain.h \
    mem/dbg.h \
    common/qbit.h \
    common/qcommon.h \
    common/qcube.h \
    common/qcubeex.h \
    common/qfrustum.h \
    common/qplane3d.h \
    common/qrect3d.h \
    common/qrect3dex.h \
    qcamera.h \
    qtglwindow.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

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
    shaders/fshader.fsh \
    shaders/vshader.vsh \
    images/cube.bmp \
    images/cube1.bmp \
    images/grass.png \
    images/grass2.jpg \
    images/heightmap128x128.png \
    images/heightmap128x128.raw \
    images/landform.png \
    images/Thumbs.db \
    images/water.png

