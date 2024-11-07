#ifndef IDATABASE_H
#define IDATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>

class IDatabase {
public:
    virtual ~IDatabase() {}

    virtual bool connect(const QString& connectionName) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;

public:
    QSqlDatabase db;
};

#endif // IDATABASE_H
