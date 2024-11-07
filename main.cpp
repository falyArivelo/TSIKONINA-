#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "./model/Recipe_Fetcher.h"
#include "./model/recipe_downloader.h"
#include "./db_connection/database_factory.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto database = DatabaseFactory::createDatabase(DatabaseFactory::DatabaseType::SQLite);

    if (database && database->connect("tsikonina")) {
        qDebug() << "Connexion à la base de données réussie.";
    } else {
        qWarning() << "Échec de la connexion à la base de données.";
    }

    QQmlApplicationEngine engine;

    RecipeFetcher recipeFetcher;
    RecipeDownloader recipeDownloader(std::move(database));
    engine.rootContext()->setContextProperty("recipeFetcher", &recipeFetcher);
    engine.rootContext()->setContextProperty("recipeDownloader", &recipeDownloader);

    const QUrl url(QStringLiteral("qrc:/TSIKONINA/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
