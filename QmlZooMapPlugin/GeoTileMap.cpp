#include "GeoTileMap.h"

GeoTileMap::GeoTileMap(QGeoTiledMappingManagerEngine *engine, QObject *parent)
    : QGeoTiledMap{engine, parent} {}
