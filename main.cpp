#include "updserver.h"
#include "updclient.h"
#include "heightindicatorwidget.h"
#include "settings.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings *settings = new Settings(&a);

    bool isServer = true;
    bool isClient = true;
    if(argc > 1){
       if(*argv[1] == 's'){
           isClient = false;
       }
       else if(*argv[1] == 's'){
           isServer = false;
       }
    }

    if(isClient){
        UpdClient clientWindow(settings);
        clientWindow.show();
    }

    if(isServer){
        UpdServer serverWindow(settings);
        serverWindow.show();

    }

    return a.exec();
}
