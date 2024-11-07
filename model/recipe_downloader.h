#ifndef RECIPE_DOWNLOADER_H
#define RECIPE_DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>
#include "../db_connection/idatabase.h"

class RecipeDownloader : public QObject
{
    Q_OBJECT

public:
    explicit RecipeDownloader(std::unique_ptr<IDatabase> database, QObject *parent = nullptr);

    Q_INVOKABLE void fetchAndSaveRecipe(const QString &mealId);

signals:
    void recipeSaved(bool success);
    void errorOccurred(const QString &errorMessage);

private slots:
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    void saveRecipeToDatabase(const QJsonObject &mealObject);

    QNetworkAccessManager *m_networkManager;
    //IDatabase *m_database;
    std::unique_ptr<IDatabase> m_database;
};

#endif // RECIPE_DOWNLOADER_H
