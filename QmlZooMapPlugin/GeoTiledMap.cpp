#include "qgeotiledmapMyMap.h"
#include "GeoTileFetcherMyMap.h"
#include <QtLocation/private/qgeotiledmappingmanagerengine_p.h>

#if QT_VERSION <= QT_VERSION_CHECK(5, 6, 0)
#include "QtLocation/private/qgeomapcontroller_p.h"
#endif

#include <QColor>
#include <QDebug>
#include <QFont>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QRect>

#include <QStaticText>

QT_BEGIN_NAMESPACE

/*!
 Constructs a new tiled map data object, which stores the map data required by
 \a geoMap and makes use of the functionality provided by \a engine.
 */
QGeoTiledMapMyMap::QGeoTiledMapMyMap(QGeoTiledMappingManagerEngine *engine,
                                     QObject *parent /*= 0*/)
    : QGeoTiledMap(engine, parent), m_engine(engine) {}

QGeoTiledMapMyMap::~QGeoTiledMapMyMap() {}

void QGeoTiledMapMyMap::setService(const QString &service) {
  auto *fetcher = qobject_cast<GeoTileFetcherMyMap *>(m_engine->tileFetcher());
  fetcher->setService(service);
}

void QGeoTiledMapMyMap::evaluateCopyrights(
    const QSet<QGeoTileSpec> &visibleTiles) {
  Q_UNUSED(visibleTiles);
}

QT_END_NAMESPACE
