#include "Recipe_Fetcher.h"
#include <QUrl>
#include <QJsonArray>

RecipeFetcher::RecipeFetcher(QObject *parent) : QObject(parent), m_networkManager(new QNetworkAccessManager(this))
{
}

void RecipeFetcher::fetchRecipes(const QString &query)
{
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &RecipeFetcher::onNetworkReplyFinished, Qt::UniqueConnection);

    QUrl url("https://www.themealdb.com/api/json/v1/1/search.php?s=" + query);
    QNetworkRequest request(url);
    m_networkManager->get(request);
}

void RecipeFetcher::onNetworkReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }

    QString jsonString = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    QVariantList recipesList;

    if (jsonObject.contains("meals")) {
        const QJsonArray &mealsArray = jsonObject["meals"].toArray();

        for (const QJsonValue &meal : mealsArray) {
            const QJsonObject &mealObject = meal.toObject();

            QVariantMap recipeMap;
            recipeMap["id"] = mealObject.value("idMeal").toString();
            recipeMap["name"] = mealObject.value("strMeal").toString();
            recipeMap["category"] = mealObject.value("strCategory").toString();
            recipeMap["area"] = mealObject.value("strArea").toString();
            recipeMap["instructions"] = mealObject.value("strInstructions").toString();
            recipeMap["imageUrl"] = mealObject.value("strMealThumb").toString();
            recipeMap["youtubeUrl"] = mealObject.value("strYoutube").toString();
            recipeMap["sourceUrl"] = mealObject.value("strSource").toString();

            QVariantList ingredients;
            QVariantList measurements;

            // Loop through ingredient and measurement fields
            for (int i = 1; i <= 20; ++i) {
                QString ingredientKey = "strIngredient" + QString::number(i);
                QString measurementKey = "strMeasure" + QString::number(i);

                QString ingredient = mealObject.value(ingredientKey).toString().trimmed();
                QString measurement = mealObject.value(measurementKey).toString().trimmed();

                if (!ingredient.isEmpty()) {
                    ingredients.append(ingredient);
                    measurements.append(measurement);
                }
            }

            recipeMap["ingredients"] = ingredients;
            recipeMap["measurements"] = measurements;

            recipesList.append(recipeMap);
        }
    }

    emit recipesFetched(recipesList);
    reply->deleteLater();
}
