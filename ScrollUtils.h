#pragma once

#include <QWheelEvent>
#include <string_view>

namespace Utils
{
    namespace Scroll
    {
        constexpr std::string_view wheelEventModificationProperty{"RequireCustomWheelEvent"};

        /*!
         * Modify QWheelEvent for pc mouse on macOS to provide mouse wheel acceleration
         * @param _event
         * @return modified event with zero pixelDelta and updated angleDelta
         */
        QWheelEvent modify(QWheelEvent* _event);

        /*!
         * Use this method if you are not passing a wheelEvent to Qt. And use it for your needs. No need to use on macOS
         * @param _angleDelta - QWheelEvent angle delta
         * @return _delta depends on QWheelEvent source and wheelScrollLines()
         */
        QPoint getAngleDelta(const QPoint& _angleDelta);

        /*!
         * Like deprecated QWheelEvent::delta
         * @return the largest component (x or y) of raw QWheelEvent::angleDelta
         */
        int getPcMouseWheelDelta(QWheelEvent* _e);

        /*!
         * @return true if raw angle delta has default delta per step (pc wheel mouse)
         */
        bool isPcMouse(QWheelEvent* _e);
    } // namespace Scroll
} // namespace Utils
