#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "IDatabase.h"
#include <QSqlError>
#include <QDebug>

class SQLiteDatabase : public IDatabase {
public:
    SQLiteDatabase();
    ~SQLiteDatabase() override;

    bool connect(const QString& connectionName) override;
    void disconnect() override;
    bool isConnected() const override;
};

#endif // SQLITEDATABASE_H
