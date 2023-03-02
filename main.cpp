#include "MainWindow.h"

#include <QApplication>
#include <MyApp.h>
#include <QDebug>
#include "Widget.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    MyApp app(argc, argv);

    qDebug() << "Start app";

    Widget w;
    w.show();
    return app.exec();
}
