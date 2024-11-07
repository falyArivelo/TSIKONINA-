#include "Recipe_Downloader.h"
#include <QUrl>
#include <QSqlQuery>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

RecipeDownloader::RecipeDownloader(std::unique_ptr<IDatabase> database, QObject *parent)
    : QObject(parent), m_database(std::move(database)), m_networkManager(new QNetworkAccessManager(this))
{
}

void RecipeDownloader::fetchAndSaveRecipe(const QString &mealId)
{
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &RecipeDownloader::onNetworkReplyFinished, Qt::UniqueConnection);

    // URL de l'API pour récupérer la recette par son ID
    QUrl url("https://www.themealdb.com/api/json/v1/1/lookup.php?i=" + mealId);
    QNetworkRequest request(url);
    m_networkManager->get(request);
}

void RecipeDownloader::onNetworkReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }

    // Traitement de la réponse JSON
    QString jsonString = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    // Si des données de repas sont retournées
    if (jsonObject.contains("meals")) {
        const QJsonArray &mealsArray = jsonObject["meals"].toArray();
        if (!mealsArray.isEmpty()) {
            const QJsonObject &mealObject = mealsArray[0].toObject();
            saveRecipeToDatabase(mealObject);  // Sauvegarde dans la base de données
        }
    }

    reply->deleteLater();
}

void RecipeDownloader::saveRecipeToDatabase(const QJsonObject &mealObject)
{ // Vérifier si la base de données est connectée
    if (!m_database->isConnected()) {
        emit errorOccurred("Database is not connected");
        return;
    }

    // Préparer la requête SQL pour insérer les données dans la table `recipes`
    QSqlQuery query(m_database->db); // Utilisation de l'objet database pour QSqlQuery

    query.prepare(R"(
        INSERT INTO recipes (
            meal_id, meal, drink_alternate, category, area, instructions, meal_thumb,
            tags, youtube, ingredients, measures, source, image_source, creative_commons_confirmed, date_modified
        ) VALUES (
            :meal_id, :meal, :drink_alternate, :category, :area, :instructions, :meal_thumb,
            :tags, :youtube, :ingredients, :measures, :source, :image_source, :creative_commons_confirmed, :date_modified
        )
    )");

    // Lier les valeurs aux paramètres SQL
    query.bindValue(":meal_id", mealObject.value("idMeal").toString());
    query.bindValue(":meal", mealObject.value("strMeal").toString());
    query.bindValue(":drink_alternate", mealObject.value("strDrinkAlternate").toString());
    query.bindValue(":category", mealObject.value("strCategory").toString());
    query.bindValue(":area", mealObject.value("strArea").toString());
    query.bindValue(":instructions", mealObject.value("strInstructions").toString());
    query.bindValue(":meal_thumb", mealObject.value("strMealThumb").toString());
    query.bindValue(":tags", mealObject.value("strTags").toString());
    query.bindValue(":youtube", mealObject.value("strYoutube").toString());

    // Gestion des ingrédients et mesures
    QJsonArray ingredientsArray;
    QJsonArray measurementsArray;
    for (int i = 1; i <= 20; ++i) {
        QString ingredientKey = "strIngredient" + QString::number(i);
        QString measurementKey = "strMeasure" + QString::number(i);

        QString ingredient = mealObject.value(ingredientKey).toString().trimmed();
        QString measurement = mealObject.value(measurementKey).toString().trimmed();

        if (!ingredient.isEmpty()) {
            ingredientsArray.append(ingredient);
            measurementsArray.append(measurement);
        }
    }

    // Convertir les tableaux JSON en chaînes et les lier
    query.bindValue(":ingredients", QJsonDocument(ingredientsArray).toJson());
    query.bindValue(":measures", QJsonDocument(measurementsArray).toJson());

    // Autres champs
    query.bindValue(":source", mealObject.value("strSource").toString());
    query.bindValue(":image_source", mealObject.value("strImageSource").toString());
    query.bindValue(":creative_commons_confirmed", mealObject.value("strCreativeCommonsConfirmed").toString());
    query.bindValue(":date_modified", mealObject.value("dateModified").toString());

    // Exécution de la requête d'insertion
    if (query.exec()) {
        emit recipeSaved(true);  // Émission du signal de succès
    } else {
        emit errorOccurred(query.lastError().text());  // En cas d'erreur
    }
}
