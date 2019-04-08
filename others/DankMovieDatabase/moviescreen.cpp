#include "moviescreen.h"
#include "ui_moviescreen.h"
#include <QJsonObject>
#include <QLabel>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

MovieScreen::MovieScreen(QWidget *parent)
    : QWidget(parent), ui(new Ui::MovieScreen) {
  ui->setupUi(this);
  movie = new QMovie(":/image/loading");
  ui->poster_image->setMovie(movie);
}

MovieScreen::~MovieScreen() { delete ui; }

QJsonObject MovieScreen::getObject() const { return object; }

void MovieScreen::setObject(const QJsonObject &value) {
  object = value;
  setInfo();
}

void MovieScreen::setInfo() {
  ui->title_label->setText(object["Title"].toString());
  QNetworkAccessManager *manager = new QNetworkAccessManager;
  QNetworkRequest request(QUrl(object["Poster"].toString()));

  QNetworkReply *reply = manager->get(request);
  connect(reply, &QNetworkReply::finished, this, &MovieScreen::setPoster);
  movie->start();
}

void MovieScreen::setPoster() {
  movie->stop();
  QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
  QByteArray bytes = reply->readAll();
  QImage img(20, 20, QImage::Format_Indexed8);
  img.loadFromData(bytes);
  ui->poster_image->setPixmap(QPixmap::fromImage(img));
}
