#include "flightroute.h"

#include <QApplication>
#include <QTimer>
#include <QWebChannel>
#include <QWebEngineView>
#include <random>

int main(int argc, char *argv[]) {
  qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9000");
  QApplication a(argc, argv);
  QWebEngineView view;

  FlightRoute routeIPC;
  QWebChannel webChannel;
  webChannel.registerObject(QStringLiteral("routeIPC"), &routeIPC);
  view.page()->setWebChannel(&webChannel);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(0, 100);

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&]() {
    QList<FPlanWPT> routes;
    for (int i = 0; i < 10; i++) {
      routes << FPlanWPT{"name1", dist(gen), dist(gen), dist(gen)};
    }
    routeIPC.setRoutes(routes);
  });
  timer.start(1000);

  view.load(QUrl(QStringLiteral("qrc:/index.html")));
  view.resize(640, 480);
  view.show();
  return a.exec();
}
