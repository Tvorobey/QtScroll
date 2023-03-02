#pragma once

#include <QApplication>

class MyApp : public QApplication
{
public:
    MyApp(int &argc, char **argv, int = ApplicationFlags);

public:
    bool notify(QObject* obj, QEvent* event);
};

