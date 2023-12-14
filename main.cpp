#include "updserver.h"
#include "updclient.h"
#include "heightindicatorwidget.h"
#include "settings.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings *settings = new Settings(&a);

    QPoint point;
    UpdClient *clientWindow;

    UpdServer *serverWindow;

    bool isServer = true;
    bool isClient = true;
    if(argc > 1){
       if(*argv[1] == 's'){
           isClient = false;
       }
       else if(*argv[1] == 'c'){
           isServer = false;
       }
    }

    if(isClient){
        clientWindow = new UpdClient(settings, a.widgetAt(point));
        clientWindow->show();
    }

    if(isServer){
        serverWindow = new UpdServer(settings, a.widgetAt(point));
        serverWindow->show();
    }

    return a.exec();
}
