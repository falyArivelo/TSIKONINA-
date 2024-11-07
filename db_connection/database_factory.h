#ifndef DATABASEFACTORY_H
#define DATABASEFACTORY_H

#include "IDatabase.h"
#include "SQLite_Database.h"
#include <memory>

class DatabaseFactory {
public:
    enum class DatabaseType {
        SQLite
        // Vous pouvez ajouter d'autres types de bases de données ici si nécessaire
    };

    static std::unique_ptr<IDatabase> createDatabase(DatabaseType type);
};

#endif // DATABASEFACTORY_H
