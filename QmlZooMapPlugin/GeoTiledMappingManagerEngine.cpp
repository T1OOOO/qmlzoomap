#include "GeoTiledMappingManagerEngine.h"
#include "GeoTileFetcher.h"
#include "GeoTileMap.h"
#include <QCoreApplication>

#include <QtLocation/private/qgeocameracapabilities_p.h>
#include <QtLocation/private/qgeofiletilecache_p.h>
#include <QtLocation/private/qgeomaptype_p.h>
#include <QtLocation/private/qgeotiledmap_p.h>

QT_BEGIN_NAMESPACE
GeoTiledMappingManagerEngineMyMap::GeoTiledMappingManagerEngineMyMap(
    const QVariantMap &parameters, QGeoServiceProvider::Error *error,
    QString *errorString) {
  QGeoCameraCapabilities camera_caps;
  camera_caps.setMinimumZoomLevel(0.0);
  camera_caps.setMaximumZoomLevel(20.0);
  camera_caps.setSupportsBearing(true);
  camera_caps.setSupportsTilting(true);
  camera_caps.setMinimumTilt(0);
  camera_caps.setMaximumTilt(80);
  camera_caps.setMinimumFieldOfView(20.0);
  camera_caps.setMaximumFieldOfView(120.0);
  camera_caps.setOverzoomEnabled(true);
  setCameraCapabilities(camera_caps);

  setTileSize(QSize(256, 256));

  QVariantMap params = parameters;

  QList<QGeoMapType> types;

  const QByteArray pluginName = "qmlzoomap";

  params["service"] = "google_map";
  types << QGeoMapType(QGeoMapType::StreetMap, tr("Google Road"),
                       tr("Normal map view in daylight mode"), false, false, 0,
                       pluginName, camera_caps, params);

  params["service"] = "google_map";
  types << QGeoMapType(QGeoMapType::SatelliteMapDay, tr("Google Satellite"),
                       tr("Satellite map view in daylight mode"), false, false,
                       1, pluginName, camera_caps, params);

  params["service"] = "google_land";
  types << QGeoMapType(QGeoMapType::TerrainMap, tr("Google Land"),
                       tr("Land map view in daylight mode"), false, false, 2,
                       pluginName, camera_caps, params);

  params["service"] = "bing_sat";
  types << QGeoMapType(QGeoMapType::SatelliteMapDay, tr("Bing Satellite"),
                       tr("Satellite map view in daylight mod"), false, false,
                       3, pluginName, camera_caps, params);

  params["service"] = "bing_roads";
  types << QGeoMapType(QGeoMapType::StreetMap, tr("Bing Road"),
                       tr("Normal map map view with streets in daylight mode"),
                       false, false, 4, pluginName, camera_caps, params);

  //  params["mapPath"] = "osm_map";
  //  types << QGeoMapType(QGeoMapType::StreetMap, tr("Osm Road"),
  //                       tr("Normal map view with streets in daylight mode"),
  //                       false, false, 5, pluginName, camera_caps, params);

  //  params["mapPath"] = "yandex_map";
  //  types << QGeoMapType(QGeoMapType::StreetMap, tr("Yandex Road"),
  //                       tr("Normal map view with streets in daylight mode"),
  //                       false, false, 6, pluginName, camera_caps, params);

  params["service"] = "yandex_sat";
  types << QGeoMapType(QGeoMapType::SatelliteMapDay, tr("Yandex Sattelite"),
                       tr("Satellite map view with streets in daylight mode"),
                       false, false, 7, pluginName, camera_caps, params);

  params["service"] = "thunderforest_forest";
  types << QGeoMapType(QGeoMapType::TerrainMap, tr("Thunderforest terrain"),
                       tr("Terrain map view with streets in daylight mode"),
                       false, false, 8, pluginName, camera_caps, params);

  params["service"] = "thunderforest_landscape";
  types << QGeoMapType(QGeoMapType::TerrainMap, tr("Thunderforest landscape"),
                       tr("Landscape map view with streets in daylight mode"),
                       false, false, 9, pluginName, camera_caps, params);

  params["service"] = "thunderforest_outdoors";
  types << QGeoMapType(QGeoMapType::TerrainMap, tr("Thunderforest outdoors"),
                       tr("Outdoors map view with streets in daylight mode"),
                       false, false, 10, pluginName, camera_caps, params);

  setSupportedMapTypes(types);

  GeoTileFetcherMyMap *tile_fetcher = new GeoTileFetcherMyMap(parameters, this);
  setTileFetcher(tile_fetcher);

  QString cache_dir =
      QAbstractGeoTileCache::baseLocationCacheDirectory() + QString("mapCache");

  QGeoFileTileCache *tile_cache = new QGeoFileTileCache(cache_dir, this);
  const int cache_size = 512 * 1024 * 1024;
  tile_cache->setMaxDiskUsage(cache_size);
  setTileCache(tile_cache);

  m_prefetchStyle = QGeoTiledMap::NoPrefetching;
  *error = QGeoServiceProvider::NoError;
  errorString->clear();
}

GeoTiledMappingManagerEngineMyMap::~GeoTiledMappingManagerEngineMyMap() {}

QGeoMap *GeoTiledMappingManagerEngineMyMap::createMap() {
  auto *map = new QGeoTiledMap(this, nullptr);
  connect(map, &QGeoTiledMap::activeMapTypeChanged, this, [this, map]() {
    auto *fetcher = qobject_cast<GeoTileFetcherMyMap *>(tileFetcher());
    fetcher->setService(map->activeMapType().metadata()["service"].toString());

    tileCache()->clearAll();
  });

  map->setPrefetchStyle(m_prefetchStyle);
  return map;
}
QT_END_NAMESPACE
