QT -= gui
QT += core
QT += network
QT += widgets
QT += qml
QT += concurrent
qtHaveModule(location-private){
    QT += location-private
}else{
    QT += location
}
qtHaveModule(positioning-private){
    QT += positioning-private
}else{
    QT += positioning
}

CONFIG += c++11
CONFIG += utf8_source

HEADERS += \
    $$PWD/GeoTileFetcher.h \
    $$PWD/GeoTileMap.h \
    $$PWD/GeoTiledMapReply.h \
    $$PWD/GeoTiledMappingManagerEngine.h \
    $$PWD/QmlZooMapFactory.h

SOURCES += \
    $$PWD/GeoTileFetcher.cpp \
    $$PWD/GeoTileMap.cpp \
    $$PWD/GeoTiledMapReply.cpp \
    $$PWD/GeoTiledMappingManagerEngine.cpp \
    $$PWD/QmlZooMapFactory.cpp

DISTFILES += \
    $$PWD/qmlzoomap_plugin.json
