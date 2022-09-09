#include "GeoTileFetcher.h"
#include "GeoTiledMapReply.h"

#include <QDebug>
#include <QUrl>
#include <QtLocation/private/qgeotilefetcher_p_p.h>
#include <QtLocation/private/qgeotilespec_p.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

static const QMap<QString, QString> MAP_PROVIDERS = {
    {"google_map", "http://mt0.google.com/vt/lyrs=m&hl=en&x=%1&y=%2&z=%3"},
    {"google_sat", "http://mt0.google.com/vt/lyrs=y&hl=ru&x=%1&y=%2&z=%3"},
    {"google_land", "http://mt0.google.com/vt/lyrs=p&hl=ru&x=%1&y=%2&z=%3"},
    {"bing_sat", "http://ecn.t0.tiles.virtualearth.net/tiles/a%1.jpeg?g=0"},
    {"bing_roads",
     "http://ecn.dynamic.t0.tiles.virtualearth.net/comp/"
     "CompositionHandler/%1?mkt=ru-ru&it=G,VE,BX,L,LA&shading=hill"},
    //    {"osm_map", "https://tile.openstreetmap.org/%3/%1/%2.png"},
    //    {"yandex_map", "http://vec04.maps.yandex.net/"
    //                   "tiles?l=map&lang=ru-RU&v=2.26.0&x=%1&y=%2&z=%3"},
    {"yandex_sat",
     "http://sat01.maps.yandex.net/tiles?l=sat&v=3.379.0&x=%1&y=%2&z=%3"},
    {"satamen_toner", "http://a.tile.stamen.com/toner/%3/%1/%2.png"},
    {"thunderforest_forest",
     "http://tile.thunderforest.com/transport/%3/%1/%2.png"},
    {"thunderforest_landscape",
     "http://tile.thunderforest.com/landscape/%3/%1/%2.png"},
    {"thunderforest_outdoors",
     "http://tile.thunderforest.com/outdoors/%3/%1/%2.png"}};

QT_BEGIN_NAMESPACE

GeoTileFetcherMyMap::GeoTileFetcherMyMap(const QVariantMap &parameters,
                                         QGeoMappingManagerEngine *parent)
    : QGeoTileFetcher(parent),
      m_networkManager(new QNetworkAccessManager(this)) {
  if (parameters.contains("service")) {
    const QString service = parameters["service"].toString();
    setService(service);
  }

  if (parameters.contains("format")) {
    m_format = parameters.value("format").toString();
  }
}

void GeoTileFetcherMyMap::setService(const QString &service) {
  if (MAP_PROVIDERS.contains(service)) {
    m_mapUrl = MAP_PROVIDERS[service];
    m_service = service;
  }
}

QGeoTiledMapReply *GeoTileFetcherMyMap::getTileImage(const QGeoTileSpec &spec) {
  QNetworkRequest request;
  request.setRawHeader("Accept", "*/*");
  request.setUrl(getUrl(spec));

  QNetworkReply *reply = m_networkManager->get(request);
  return new GeoTiledMapReplyMyMap(reply, spec, m_format);
}

QString GeoTileFetcherMyMap::getUrl(const QGeoTileSpec &spec) const {
  QUrl url;

  if (m_service.startsWith("bing")) {
    QString key;
    for (int i = spec.zoom(); i > 0; i--) {
      char digit = '0';
      int mask = 1 << (i - 1);
      if ((spec.x() & mask) != 0)
        digit++;
      if ((spec.y() & mask) != 0)
        digit += 2;

      key.append(digit);
    }
    url.setUrl(m_mapUrl.arg(key));
  } else {
    url.setUrl(m_mapUrl.arg(spec.x()).arg(spec.y()).arg(spec.zoom()));
  }

  QString str = url.toString();

  return str;
}

QT_END_NAMESPACE
