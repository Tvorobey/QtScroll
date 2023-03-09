#include "Widget.h"
#include "MyApp.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}
