#include "updserver.h"
#include "updclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UpdClient clientWindow;
    clientWindow.show();

    UpdServer serverWindow;
    serverWindow.show();

    return a.exec();
}
