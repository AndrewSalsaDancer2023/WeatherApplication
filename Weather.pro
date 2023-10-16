QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addlocationdialog.cpp \
    addlocationdialogcoordinator.cpp \
    asyncdownloader.cpp \
    circularprogresswidget.cpp \
    contentdownloader.cpp \
    coordinator.cpp \
    detailforecastwidget.cpp \
    fivedayforecastwidget.cpp \
    forecastmodel.cpp \
    forecastsettings.cpp \
    geocoder.cpp \
    geocodingparameters.cpp \
    imagecache.cpp \
    main.cpp \
    settingsdialog.cpp \
    settingsdialogcoordinator.cpp \
    settingstore.cpp \
    shortforecastwidget.cpp \
    utilities.cpp \
    waithintdialog.cpp \
    weatherwindow.cpp

HEADERS += \
    addlocationdialog.h \
    addlocationdialogcoordinator.h \
    asyncdownloader.h \
    circularprogresswidget.h \
    contentdownloader.h \
    coordinator.h \
    detailforecastwidget.h \
    fivedayforecastwidget.h \
    forecastmodel.h \
    forecastsettings.h \
    geocoder.h \
    geocodingparameters.h \
    imagecache.h \
    settingsdialog.h \
    settingsdialogcoordinator.h \
    settingstore.h \
    shortforecastwidget.h \
    threadsupport.h \
    utilities.h \
    waithintdialog.h \
    weatherwindow.h

FORMS += \
    addlocationdialog.ui \
    detailforecastwidget.ui \
    fivedayforecastwidget.ui \
    settingsdialog.ui \
    shortforecastwidget.ui \
    waithintdialog.ui \
    weatherwindow.ui

TRANSLATIONS += \
    Weather_ru_RU.ts

LIBS += -lboost_thread
RC_FILE=res.rc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    icon.ico
