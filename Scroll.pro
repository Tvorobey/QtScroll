QT += core gui widgets

CONFIG += c++17

SOURCES += \
    MyApp.cpp \
    ScrollUtils.cpp \
    Widget.cpp \
    main.cpp

HEADERS += \
    MyApp.h \
    ScrollUtils.h \
    Widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
