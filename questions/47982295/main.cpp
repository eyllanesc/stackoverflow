#include <QApplication>
#include <QPushButton>
#include <QQmlApplicationEngine>
#include "mainmenu.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    MainMenu M;
    M.show();//screen 2(main menu, which has "Start" button)

    QQmlApplicationEngine engine;
    QPushButton *button = M.findChild<QPushButton *>("StartButton");
    engine.rootContext()->setContextProperty("button", button);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
