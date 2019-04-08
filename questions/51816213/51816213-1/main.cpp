#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QNetworkAccessManager manager;

  QObject::connect(&manager, &QNetworkAccessManager::finished,
                   [](QNetworkReply *reply) {
                     qDebug() << reply->readAll();
                     delete reply;
                     QCoreApplication::quit();
                   });
  QNetworkRequest request(
      QUrl("http://hapi.fhir.org/baseDstu3/Patient/4705560"));
  request.setRawHeader("Content-Type", "application/fhir+json");
  QFile file("themostsimplepatientJSON.json");
  if (!file.open(QIODevice::ReadOnly))
    return -1;

  QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
  QJsonObject obj = doc.object();
  obj["id"] = "4705560";
  doc.setObject(obj);
  manager.put(request, doc.toJson());
  // manager.post(request, &file);

  return a.exec();
}
