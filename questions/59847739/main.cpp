#include "sqlquerymodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QSqlError>

static bool createConnection()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        qDebug()<<"Cannot open database\n"
                  "Unable to establish a database connection.\n"
                  "This example needs SQLite support. Please read "
                  "the Qt SQL driver documentation for information how "
                  "to build it.\n\n"
                  "Click Cancel to exit.";
        return false;
    }
    QSqlQuery query;
    return query.exec(R"(CREATE TABLE "results" (
                      "id" INTEGER PRIMARY KEY AUTOINCREMENT,
                      "Semester" TEXT,
                      "CourseTitle" TEXT,
                      "TestWeight" TEXT,
                      "TestName" TEXT,
                      "Result" INTEGER,
                      "OutOf" INTEGER
                      )
                      )");
}


int main(int argc, char *argv[])
{
    qmlRegisterType<SqlQueryModel>("GradesSqlDataModel", 1, 0, "SqlQueryModel");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    if(!createConnection())
        return -1;

    QSqlQuery query;
    query.exec("INSERT INTO results (Semester, CourseTitle, TestWeight, TestName, Result, OutOf) VALUES ('Spring 2020', 'Course 1', '10', 'Exam 1', 50, 100)");
    query.exec("INSERT INTO results (Semester, CourseTitle, TestWeight, TestName, Result, OutOf) VALUES ('Spring 2020', 'Course 1', '33', 'Exam 2', 70, 100)");
    query.exec("INSERT INTO results (Semester, CourseTitle, TestWeight, TestName, Result, OutOf) VALUES ('Spring 2020', 'Course 2', '25', 'Exam 1', 0, 100)");
    query.exec("INSERT INTO results (Semester, CourseTitle, TestWeight, TestName, Result, OutOf) VALUES ('Spring 2020', 'Course 2', '5', 'Quiz 1', 5, 20)");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
