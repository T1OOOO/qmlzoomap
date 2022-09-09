#pragma once
#include <QNetworkAccessManager>
#include <QtLocation/private/qgeotilefetcher_p.h>

QT_BEGIN_NAMESPACE

class GeoTileFetcherMyMap : public QGeoTileFetcher {
  Q_OBJECT
public:
  GeoTileFetcherMyMap(const QVariantMap &parameters,
                      QGeoMappingManagerEngine *parent);
  void setService(const QString &service);

private:
  QGeoTiledMapReply *getTileImage(const QGeoTileSpec &spec) override;
  QString getUrl(const QGeoTileSpec &spec) const;

private:
  QString m_mapUrl;
  QString m_service;
  QString m_format{"png"};
  QNetworkAccessManager *m_networkManager;
};
QT_END_NAMESPACE
