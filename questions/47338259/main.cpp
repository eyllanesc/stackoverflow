#include <QApplication>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

class Helper : public QObject
{
    Q_OBJECT
    QWidgetList widgets;
public:
    Q_INVOKABLE void closeAllWidgets(){
        for(QWidget *w: widgets)
            w->close();
    }
    void addWidget(QWidget *w){
        widgets<<w;
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Helper helper;
    engine.rootContext()->setContextProperty("helper", &helper);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    for(int i=1; i < 5; i++){
        QMessageBox* errorD = new QMessageBox();
        helper.addWidget(errorD);
        errorD->setStandardButtons(QMessageBox::Ok);
        errorD->setDefaultButton(QMessageBox::Ok);
        errorD->setModal(false);
        errorD->setWindowTitle("title");
        errorD->setText("msg");
        // We reset when closed
        QObject::connect(errorD, &QMessageBox::destroyed, [=]() { printf("QMBox destroyed.");});
        errorD->raise();
        errorD->activateWindow();
        errorD->show();
        QApplication::processEvents();
    }

    return app.exec();
}
