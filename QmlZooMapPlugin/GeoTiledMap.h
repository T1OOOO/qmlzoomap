#ifndef QGEOMAPGOOGLEMAPS_H
#define QGEOMAPGOOGLEMAPS_H

#include "QtLocation/private/qgeotiledmap_p.h"
#include <QtCore/QPointer>
#include <QtGui/QImage>

QT_BEGIN_NAMESPACE

class QGeoTiledMapMyMap : public QGeoTiledMap {
  Q_OBJECT
public:
  QGeoTiledMapMyMap(QGeoTiledMappingManagerEngine *engine, QObject *parent = 0);
  ~QGeoTiledMapMyMap();

  // Q_PROPERTY(QString service WRITE setService)

  void setService(const QString &service);

  QString getViewCopyright();
  void evaluateCopyrights(const QSet<QGeoTileSpec> &visibleTiles);

private:
  // QImage m_logo;
  QImage m_copyrightsSlab;
  QString m_lastCopyrightsString;
  QPointer<QGeoTiledMappingManagerEngine> m_engine;

  Q_DISABLE_COPY(QGeoTiledMapMyMap)
};

QT_END_NAMESPACE

#endif // QGEOMAPGOOGLEMAPS_H
