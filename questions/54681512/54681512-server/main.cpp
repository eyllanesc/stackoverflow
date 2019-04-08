#include "minimalsource.h"

#include <QCoreApplication>
#include <QRemoteObjectHost>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  MinimalSource remoteSource;

  QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:remote_minimal")));
  srcNode.enableRemoting(&remoteSource);
  return a.exec();
}
