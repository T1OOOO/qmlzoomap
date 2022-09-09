#pragma once

#include <QtLocation/private/qgeotiledmap_p.h>

class GeoTileMap : public QGeoTiledMap {
  Q_OBJECT
public:
  explicit GeoTileMap(QGeoTiledMappingManagerEngine *engine,
                      QObject *parent = nullptr);

signals:
};
