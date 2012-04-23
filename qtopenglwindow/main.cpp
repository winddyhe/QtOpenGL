#include "qtgamewindow.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QtGameWindow w;
    w.showFullScreen();

    return app.exec();
}
