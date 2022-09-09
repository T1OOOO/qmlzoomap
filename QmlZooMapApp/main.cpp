#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtPlugin>

#ifdef MyMapPlugin_Static
#include <QtPlugin>
#endif

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

#ifdef QmlZooMapPlugin_Static
  Q_IMPORT_PLUGIN(QmlZooMapPlugin);
#endif

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty(
      "applicationDirPath", QGuiApplication::applicationDirPath());

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
