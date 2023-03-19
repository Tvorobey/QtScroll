#include "MyApp.h"

#include "ScrollUtils.h"

MyApp::MyApp(int& _argc, char** _argv, int)
    : QApplication(_argc, _argv)
{}

void MyApp::setRequireCustomWheelEvent(QScrollBar* _slider, bool _on)
{
    _slider->setProperty(Utils::Scroll::wheelEventModificationProperty.data(), _on);
}

bool MyApp::notify(QObject* _obj, QEvent* _event)
{
#ifdef __APPLE__
    if (_event->type() != QEvent::Wheel)
        return QApplication::notify(_obj, _event);

    if (auto scrollbar = qobject_cast<QScrollBar*>(_obj))
    {
        const QVariant value = _obj->property(Utils::Scroll::wheelEventModificationProperty.data());

        if (value.isValid() && value.toBool())
        {
            QWheelEvent wheelEvent = Utils::Scroll::modify(static_cast<QWheelEvent*>(_event));
            scrollbar->event(&wheelEvent);
            return true;
        }
    }
#endif

    return QApplication::notify(_obj, _event);
}
