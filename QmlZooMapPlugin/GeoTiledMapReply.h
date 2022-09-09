#pragma once
#include <QtLocation/private/qgeotiledmapreply_p.h>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE

class GeoTiledMapReplyMyMap : public QGeoTiledMapReply {
  Q_OBJECT

public:
  GeoTiledMapReplyMyMap(QNetworkReply *reply, const QGeoTileSpec &spec,
                        const QString &imageFormat, QObject *parent = nullptr);

private Q_SLOTS:
  void networkReplyFinished();
  void networkReplyError(QNetworkReply::NetworkError error);
};
QT_END_NAMESPACE
