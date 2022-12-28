QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chooseusers.cpp \
    enterwindow.cpp \
    group.cpp \
    logic.cpp \
    main.cpp \
    mainwindow.cpp \
    registration.cpp

HEADERS += \
    chooseusers.h \
    enterwindow.h \
    group.h \
    logic.h \
    mainwindow.h \
    registration.h

FORMS += \
    chooseusers.ui \
    enterwindow.ui \
    group.ui \
    mainwindow.ui \
    registration.ui


win32: RC_FILE = iconClient.rc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
