#include <QCoreApplication>

#include <ConsoleAppender.h>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    ConsoleAppender *consoleAppender = new ConsoleAppender;
    consoleAppender->setFormat("[%{type:-7}] <%{Function}> %{message}\n");
    cuteLogger->registerAppender(consoleAppender);

    LOG_INFO("Starting the application");
    int result = app.exec();

    if (result)
        LOG_WARNING() << "Something went wrong." << "Result code is" << result;
    return result;
}
