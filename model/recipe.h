#ifndef RECIPE_H
#define RECIPE_H

#include <QString>
#include <QVector>
#include <QJsonArray>

class Recipe {
public:
    enum Category { Appetizer, MainCourse, Dessert, SideDish ,Unknown};
    enum Area { American, British, Italian, Mexican };

    // Constructeur avec validation
    Recipe(int id = 0, const QString& name = "", const Category category = Category::Appetizer,
           const QString& area = "", const QString& instructions = "",
           const QString& imageUrl = "", const QString& youtubeUrl = "",
           const QString& sourceUrl = "");

    // Getters
    int getId() const;
    QString getName() const;
    Category getCategory() const;
    QString getArea() const;
    QString getInstructions() const;
    QString getImageUrl() const;
    QString getYoutubeUrl() const;
    QString getSourceUrl() const;

    // Setters avec validation
    void setId(int id);
    void setName(const QString& name);
    void setCategory(Category category);
    void setArea(const QString& area);
    void setInstructions(const QString& instructions);
    void setImageUrl(const QString& imageUrl);
    void setYoutubeUrl(const QString& youtubeUrl);
    void setSourceUrl(const QString& sourceUrl);

    // Méthode pour récupérer toutes les informations sous forme de chaîne
    QString toString() const;

    // Méthode pour convertir en objet JSON
    QJsonObject toJSON() const;

    void addIngredient(const QString& ingredient, const QString& measurement) ;

    QList<QString> getIngredients() const;

    QList<QString> getMeasurements() const ;


private:
    int id;
    QString name;
    Category category;
    QString area;
    QString instructions;
    QString imageUrl;
    QString youtubeUrl;
    QString sourceUrl;

    QVector<QString> ingredients;
    QVector<QString> measurements;

    // Autres méthodes privées...
};

#endif // RECIPE_H
