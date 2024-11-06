#ifndef RECIPE_FETCHER_H
#define RECIPE_FETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantList>
#include "Recipe.h"

class RecipeFetcher : public QObject
{
    Q_OBJECT

public:
    explicit RecipeFetcher(QObject *parent = nullptr);

    Q_INVOKABLE void fetchRecipes(const QString &query);  // Method callable from QML

signals:
    void recipesFetched(const QVariantList &recipes);     // Signal to emit recipes as QVariantList
    void errorOccurred(const QString &errorMessage);

private slots:
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
};

#endif // RECIPE_FETCHER_H
