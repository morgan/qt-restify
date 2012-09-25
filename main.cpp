#include <QApplication>
#include "restify.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    Restify restify;
    restify.show();

    return app.exec();
}
