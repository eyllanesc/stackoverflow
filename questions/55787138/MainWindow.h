#pragma once

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TableModel.h"

class MainWindow : public QObject {
    Q_OBJECT
public:
    explicit MainWindow() {
        engine_.rootContext()->setContextProperty("myModel", &model_);
        engine_.load(QUrl(QStringLiteral("qrc:/main.qml")));
    }
private:
    TableModel model_;
    QQmlApplicationEngine engine_;
};
