#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>

class StringListModel: public QStringListModel{
    Q_OBJECT
public:
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()){
        return QStringListModel::removeRows(row, count, parent);
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QStringList l{"a", "b", "c", "d"};
    StringListModel model;
    model.setStringList(l);
    engine.rootContext()->setContextProperty("myModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
