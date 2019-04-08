#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  nam = new QNetworkAccessManager(this);
  connect(nam, &QNetworkAccessManager::finished, this, &MainWindow::onResult);

  QString lang = "ar";
  QString text = "Hello World";
  QString key = "trnsl.1.1.20180627T161429Z.7e64c91dd2016a6c."
                "9901da9a44bc324388a2460776ab55b2d72b4c5a";

  QUrlQuery query;
  query.addQueryItem("key", key);
  query.addQueryItem("lang", lang);
  query.addQueryItem("text", text);

  QUrl url("https://translate.yandex.net/api/v1.5/tr.json/translate");
  url.setQuery(query);

  qDebug() << "url: " << url.toString(QUrl::FullyEncoded);

  nam->get(QNetworkRequest(url));
}

void MainWindow::onResult(QNetworkReply *reply) {
  if (reply->error() == QNetworkReply::NoError) {

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    QJsonObject obj = jsonResponse.object();
    qDebug() << "code: " << obj["code"].toInt();
    qDebug() << "lang: " << obj["lang"].toString();
    QJsonArray array = obj["text"].toArray();

    for (const QJsonValue &value : array) {
      qDebug() << "text: " << value.toString();
    }
  } else
    qDebug() << "ERROR";
  reply->deleteLater();
}
MainWindow::~MainWindow() { delete ui; }
