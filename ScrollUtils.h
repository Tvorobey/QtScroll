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
    } // namespace Scroll
} // namespace Utils
