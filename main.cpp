#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDir>
#include <QtDebug>
#include <QQmlContext>

#include "addnewdata.h"

static void connectToDatabase()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        qFatal("Unable to load database, This demo needs the SQLITE driver");
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!writeDir.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    // Ensure that we have a writable location on all devices.
    const QString fileName = writeDir.absolutePath() + "/music-organizer-db.sqlite3";
    qDebug() << "db dir is:" << fileName;
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(fileName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Music Organization");
    QGuiApplication::setOrganizationName("AliJafari");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<AddNewData>("alijafari.musicorganizer", 1, 0, "AddNewData");

    QIcon::setThemeName("icons");

    QQuickStyle::setStyle("Material");

    connectToDatabase();

    QQmlApplicationEngine engine;
    AddNewData addNewData;
    engine.rootContext()->setContextProperty("addNewData", &addNewData);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
