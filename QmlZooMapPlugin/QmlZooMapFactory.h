#pragma once
#include <QObject>
#include <QtLocation/QGeoServiceProviderFactory>

QT_BEGIN_NAMESPACE

class QmlZooMapFactory : public QObject, public QGeoServiceProviderFactory {
  Q_OBJECT
  Q_INTERFACES(QGeoServiceProviderFactory)
  Q_PLUGIN_METADATA(
      IID "org.qt-project.qt.geoservice.serviceproviderfactory/5.0" FILE
          "qmlzoomap_plugin.json")
public:
  QmlZooMapFactory();

  // QGeoCodingManagerEngine *createGeocodingManagerEngine(const QVariantMap
  // &parameters,
  //                                                       QGeoServiceProvider::Error
  //                                                       *error, QString
  //                                                       *errorString) const;
  // QGeoRoutingManagerEngine *createRoutingManagerEngine(const QVariantMap
  // &parameters,
  //                                                      QGeoServiceProvider::Error
  //                                                      *error, QString
  //                                                      *errorString) const;
  // QPlaceManagerEngine *createPlaceManagerEngine(const QVariantMap
  // &parameters,
  //                                               QGeoServiceProvider::Error
  //                                               *error, QString *errorString)
  //                                               const;
  QGeoMappingManagerEngine *
  createMappingManagerEngine(const QVariantMap &parameters,
                             QGeoServiceProvider::Error *error,
                             QString *errorString) const;
};
QT_END_NAMESPACE
