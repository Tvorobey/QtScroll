#include "MyApp.h"

#include <QDebug>
#include <QScrollBar>
#include <ScrollUtils.h>

MyApp::MyApp(int& argc, char** argv, int)
    : QApplication(argc, argv)
{}

bool MyApp::notify(QObject* obj, QEvent* event)
{
#ifdef __APPLE__
    if (event->type() != QEvent::Wheel)
        return QApplication::notify(obj, event);

    if (auto scrollbar = qobject_cast<QScrollBar*>(obj))
    {
        const QVariant value = obj->property(Utils::Scroll::wheelEventModificationProperty.data());

        if (value.isValid() && value.toBool())
        {
            qDebug() << "Modify wheel event for: " << scrollbar->objectName();
            QWheelEvent wheelEvent = Utils::Scroll::modify(static_cast<QWheelEvent*>(event));
            scrollbar->event(&wheelEvent);
            return true;
        }
    }
#endif

    return QApplication::notify(obj, event);
}
