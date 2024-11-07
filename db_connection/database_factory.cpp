#include "Database_Factory.h"

std::unique_ptr<IDatabase> DatabaseFactory::createDatabase(DatabaseType type) {
    switch (type) {
    case DatabaseType::SQLite:
        return std::make_unique<SQLiteDatabase>();
    // Ajouter des cas pour d'autres types de bases de données si nécessaire
    default:
        return nullptr;
    }
}
