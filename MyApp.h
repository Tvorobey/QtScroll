#pragma once

#include <QApplication>
#include <QScrollBar>

class MyApp : public QApplication
{
public:
    MyApp(int& _argc, char** _argv, int = ApplicationFlags);
    static void setRequireCustomWheelEvent(QScrollBar* _slider, bool _on = true);

public:
    bool notify(QObject* _obj, QEvent* _event);
};
