#include "recipe.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QStringList>

Recipe::Recipe(int id, const QString& name, Category category, const QString& area,
               const QString& instructions, const QString& imageUrl, const QString& youtubeUrl,
               const QString& sourceUrl)
    : id(id), name(name), category(category), area(area), instructions(instructions),
    imageUrl(imageUrl), youtubeUrl(youtubeUrl), sourceUrl(sourceUrl)
{
    // Validation basique
    if (id <= 0 || name.isEmpty() || area.isEmpty()) {
        throw std::invalid_argument("Invalid recipe data");
    }
}

int Recipe::getId() const { return id; }

QString Recipe::getName() const { return name; }

Recipe::Category Recipe::getCategory() const { return category; }

QString Recipe::getArea() const { return area; }

QString Recipe::getInstructions() const { return instructions; }

QString Recipe::getImageUrl() const { return imageUrl; }

QString Recipe::getYoutubeUrl() const { return youtubeUrl; }

QString Recipe::getSourceUrl() const { return sourceUrl; }

void Recipe::setId(int id) {
    if (id > 0) {
        this->id = id;
    } else {
        throw std::invalid_argument("ID must be positive");
    }
}

void Recipe::setName(const QString& name) {
    if (!name.isEmpty()) {
        this->name = name;
    } else {
        throw std::invalid_argument("Name cannot be empty");
    }
}

void Recipe::setCategory(Category category) {
    if (category != Category::Unknown) {
        this->category = category;
    } else {
        throw std::invalid_argument("Invalid category");
    }
}

void Recipe::setArea(const QString& area) {
    if (!area.isEmpty()) {
        this->area = area;
    } else {
        throw std::invalid_argument("Area cannot be empty");
    }
}

void Recipe::setInstructions(const QString& instructions) {
    if (!instructions.isEmpty()) {
        this->instructions = instructions;
    } else {
        throw std::invalid_argument("Instructions cannot be empty");
    }
}

void Recipe::setImageUrl(const QString& imageUrl) {
    if (!imageUrl.isEmpty()) {
        this->imageUrl = imageUrl;
    } else {
        throw std::invalid_argument("Image URL cannot be empty");
    }
}

void Recipe::setYoutubeUrl(const QString& youtubeUrl) {
    if (!youtubeUrl.isEmpty()) {
        this->youtubeUrl = youtubeUrl;
    } else {
        throw std::invalid_argument("YouTube URL cannot be empty");
    }
}

void Recipe::setSourceUrl(const QString& sourceUrl) {
    if (!sourceUrl.isEmpty()) {
        this->sourceUrl = sourceUrl;
    } else {
        throw std::invalid_argument("Source URL cannot be empty");
    }
}

void Recipe::addIngredient(const QString& ingredient, const QString& measurement) {
    ingredients.append(ingredient);
    measurements.append(measurement);
}

QList<QString> Recipe::getIngredients() const { return ingredients; }

QList<QString> Recipe::getMeasurements() const { return measurements; }

QString Recipe::toString() const {
    QStringList fields;
    fields << "ID: " + QString::number(id)
           << "Name: " + name

                  //<< "Category: " + static_cast<const char*>(static_cast<void*>(&category))
           << "Area: " + area
           << "Instructions: " + instructions
           << "Image URL: " + imageUrl
           << "YouTube URL: " + youtubeUrl
           << "Source URL: " + sourceUrl;

    // Ajouter les ingrédients et mesures si présents
    if (!ingredients.empty()) {
        fields << "Ingredients:" << ingredients.join(", ");
        fields << "Measurements:" << measurements.join(", ");
    }

    return fields.join("\n");
}


QJsonObject Recipe::toJSON() const {
    QJsonObject jsonObject;

    jsonObject.insert("id", id);
    jsonObject.insert("name", name);
    jsonObject.insert("category", static_cast<int>(category));
    jsonObject.insert("area", area);
    jsonObject.insert("instructions", instructions);
    jsonObject.insert("imageUrl", imageUrl);
    jsonObject.insert("youtubeUrl", youtubeUrl);
    jsonObject.insert("sourceUrl", sourceUrl);

    if (!ingredients.empty()) {
        QJsonArray ingredientsArray;
        for (const auto& ing : ingredients) {
            ingredientsArray.append(ing);
        }
        jsonObject.insert("ingredients", ingredientsArray);

        QJsonArray measurementsArray;
        for (const auto& meas : measurements) {
            measurementsArray.append(meas);
        }
        jsonObject.insert("measurements", measurementsArray);
    }

    return jsonObject;
}
