#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardItemModel>

class MyStandardModel : public QStandardItemModel {
  Q_OBJECT
public:
  enum Role { role1 = Qt::UserRole + 1, role2 };

  using QStandardItemModel::QStandardItemModel;

  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[role1] = "one";
    roles[role2] = "two";
    return roles;
  }

  Q_INVOKABLE void updateValue(int row, QVariant value,
                               const QString &roleName) {

    int role = roleNames().key(roleName.toUtf8());
    QStandardItem *it = item(row);
    if (it) {
      blockSignals(true);
      it->setData(value, role);
      Q_ASSERT(it->data(role) == value);
      blockSignals(false);
    }
  }
};

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  MyStandardModel model;

  for (int i = 0; i < 10; i++) {
    auto item = new QStandardItem;
    item->setData(QString("data1 %1").arg(i), MyStandardModel::role1);
    if (i % 2 == 0)
      item->setData(true, MyStandardModel::role2);
    else {
      item->setData(QString("data2 %1").arg(i), MyStandardModel::role2);
    }
    model.appendRow(item);
  }
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("myTestModel", &model);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}

#include "main.moc"
