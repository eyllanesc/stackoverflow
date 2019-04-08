#include "appendproxymodel.h"
#include "connection.h"

#include <QApplication>
#include <QComboBox>
#include <QIdentityProxyModel>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>

#include <QDebug>
#include <QTimer>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  if (!createConnection()) {
    return -1;
  }
  QComboBox combo;
  QSqlQueryModel model;
  model.setQuery("select DISTINCT firstname from person");
  AppendProxyModel proxy;
  proxy.setDefaults({"all", "option1", "option2"});
  proxy.setSourceModel(&model);
  QObject::connect(&combo, &QComboBox::currentTextChanged,
                   [](const QString &currentText) {
                     qDebug() << "currentText: " << currentText;
                   });
  QTimer::singleShot(1000, [&model]() {
    model.setQuery("select DISTINCT lastname from person");
  });
  combo.setModel(&proxy);
  combo.show();

  return a.exec();
}
