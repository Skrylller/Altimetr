#include "updserver.h"
#include "updclient.h"
#include "heightindicatorwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UpdClient clientWindow;
    clientWindow.show();

    UpdServer serverWindow;
    serverWindow.show();

    HeightIndicatorWidget heightIndicator;
    heightIndicator.show();

    return a.exec();
}
