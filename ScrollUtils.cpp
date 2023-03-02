#include "ScrollUtils.h"

#include <QApplication>

namespace
{
    int updateAngleDeltaComponent(int _component)
    {
        if (_component % QWheelEvent::DefaultDeltasPerStep != 0) // win trackpad or mouse with not standard wheel
        {
            return _component;
        }
        else // standard mouse wheel
        {
            const int numDegrees = _component / 8;
            return numDegrees * qApp->wheelScrollLines();
        }
    }
} // namespace

namespace Utils::Scroll
{
    QWheelEvent modify(QWheelEvent* _event)
    {
#ifdef __APPLE__
            if (_event->source() == Qt::MouseEventNotSynthesized)
            {
                const QPoint numPixels = _event->pixelDelta();
                const QPoint numDegrees = _event->angleDelta();

                QPoint delta {};

                if (!numPixels.isNull())
                    delta = numPixels;
                else if (!numDegrees.isNull())
                    delta = getAngleDelta(numDegrees);

                delta *= 2;

                return { _event->position(), _event->globalPosition(), {}, delta, _event->buttons(), _event->modifiers(), _event->phase(),
                         _event->inverted(), _event->source() };
            }
#endif

        return { _event->position(),  _event->globalPosition(), _event->pixelDelta(), _event->angleDelta(), _event->buttons(),
                 _event->modifiers(), _event->phase(),          _event->inverted(),   _event->source() };
    }

    QPoint getAngleDelta(const QPoint& _angleDelta)
    {
        return { updateAngleDeltaComponent(_angleDelta.x()), updateAngleDeltaComponent(_angleDelta.y()) };
    }

    int getPcMouseWheelDelta(QWheelEvent* _e)
    {
        int delta { 0 };

        const QPoint scrollDelta = _e->angleDelta();

        if (scrollDelta.x() != 0 && scrollDelta.y() != 0)
            delta = std::max(qAbs(scrollDelta.x()), qAbs(scrollDelta.y()));
        else
            delta = scrollDelta.x() != 0 ? scrollDelta.x() : scrollDelta.y();

        return delta;
    }

    bool isPcMouse(QWheelEvent* _e)
    {
        if (_e->source() == Qt::MouseEventSynthesizedBySystem)
            return false;

        return getPcMouseWheelDelta(_e) % QWheelEvent::DefaultDeltasPerStep == 0;
    }
} // namespace Utils::Scroll
