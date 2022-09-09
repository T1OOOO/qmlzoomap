QT += core
QT += gui
QT += widgets
QT += quick
QT += qml
QT += network
QT += concurrent
QT += location
QT += positioning

TEMPLATE = app

CONFIG += c++11
CONFIG += utf8_source
CONFIG += resources_big

DESTDIR = $$PWD/../bin
CONFIG(debug, debug|release){
#    LIBS += $$PWD/../plugin/MyMapPlugind.lib
    TARGET = QmlZooMapAppd
}
else{
#    LIBS += $$PWD/../plugin/MyMapPlugin.lib
    TARGET = QmlZooMapApp
}

# using static plugin at demo
DEFINES += QmlZooMapPlugin_Static
contains(DEFINES,QmlZooMapPlugin_Static){
    INCLUDEPATH += $$PWD/../QmlZooMapPlugin
    include($$PWD/../QmlZooMapPlugin/QmlZooMapPlugin.pri)

    LOCATION_PLUGIN_DESTDIR = $${OUT_PWD}/QmlZooMapPlugin
    LOCATION_PLUGIN_NAME    = QmlZooMapFactory
}

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp

RESOURCES += $$PWD/QML/qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
