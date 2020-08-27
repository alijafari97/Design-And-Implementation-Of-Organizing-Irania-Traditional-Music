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
#include <QQmlComponent>

#include "addnewdata.h"
#include "searchmusic.h"

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
    qmlRegisterType<SearchMusic>("alijafari.musicorganizer", 1, 0, "SearchMusic");

    QIcon::setThemeName("icons");

    QQuickStyle::setStyle("Material");

    connectToDatabase();

    QQmlEngine engine;
//    QList<QObject *> dataList = {
////            new DataObject("Item 1", "red", "0"),
////            new DataObject("Item 2", "green", "0"),
////            new DataObject("Item 3", "blue", "1"),
////            new DataObject("Item 4", "yellow", "1")
//        };
//    engine.rootContext()->setContextProperty("resultModel", QVariant::fromValue(dataList)) ;
    SearchMusic searchMusic(&engine, NULL);
    searchMusic.responseToUi(true);

    QQmlComponent component(&engine, "qrc:/main.qml");
    QObject *object = component.create();
    searchMusic.setMainQml(object);
//    SearchMusic searchMusic(object, &engine, NULL);
    AddNewData addNewData;
    engine.rootContext()->setContextProperty("addNewData", &addNewData);
    engine.rootContext()->setContextProperty("searchMusci", &searchMusic);

    QMetaObject::invokeMethod(object, "showAbout");
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
