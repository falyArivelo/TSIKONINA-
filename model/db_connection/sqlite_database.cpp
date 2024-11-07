#ifndef DATABASEFACTORY_H
#define DATABASEFACTORY_H

#include "IDatabase.h"
#include "SQLite_Database.h"

class DatabaseFactory {
public:
    static IDatabase* createDatabase(const QString& type) {
        if (type == "QSQLITE") {
            return new SQLiteDatabase();
        }
        // Ajouter d'autres types de bases de données ici (par exemple, MySQL, PostgreSQL)
        return nullptr;
    }
};

#endif // DATABASEFACTORY_H
