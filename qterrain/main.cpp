
#include "qtglwindow.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QtGLWindow w;
    w.showFullScreen();

    return app.exec();
}
