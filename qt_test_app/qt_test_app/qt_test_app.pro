QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_test_app
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

#CONFIG += build_all

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

windows {
    contains(QMAKE_TARGET.arch, x86_64) {
        *-msvc*: LIBS += -L$$PWD/../libusb-1.0.22/MS64/dll/
        *-g++*: LIBS += -L$$PWD/../libusb-1.0.22/MinGW64/dll/
    } else {
        *-msvc*: LIBS += -L$$PWD/../libusb-1.0.22/MS32/dll/
        *-g++*: LIBS += -L$$PWD/../libusb-1.0.22/MinGW32/dll/
    }

    *-msvc*: LIBS += -llibusb-1.0
    *-g++*: LIBS += libusb-1.0.dll

    INCLUDEPATH += $$PWD/../libusb-1.0.22/include/libusb-1.0

    Debug: dlls.path = $$OUT_PWD/debug
    Release: dlls.path = $$OUT_PWD/release

    contains(QMAKE_TARGET.arch, x86_64) {
        *-msvc*: dlls.files = $$PWD/../libusb-1.0.22/MS64/dll/libusb-1.0.dll
        *-g++*: dlls.files = $$PWD/../libusb-1.0.22/MinGW64/dll/libusb-1.0.dll
    } else {
        *-msvc*: dlls.files = $$PWD/../libusb-1.0.22/MS32/dll/libusb-1.0.dll
        *-g++*: dlls.files = $$PWD/../libusb-1.0.22/MinGW32/dll/libusb-1.0.dll
    }

    INSTALLS += dlls
}

unix {
    #TODO!!!#
}
