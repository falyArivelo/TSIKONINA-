#include "SQLite_Database.h"

SQLiteDatabase::SQLiteDatabase() {
    // Constructeur par défaut
}

SQLiteDatabase::~SQLiteDatabase() {
    disconnect(); // Ferme la connexion si elle est encore ouverte
}

bool SQLiteDatabase::connect(const QString& connectionName) {
    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName("Tsikonina_DB.db"); // Nom de fichier de la base de données SQLite
    }

    if (!db.open()) {
        qDebug() << "Failed to open SQLite database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec("PRAGMA foreign_keys = ON;")) {
        qWarning() << "Error enabling foreign key constraints:" << query.lastError().text();
    }

    qDebug() << "Connected to SQLite database successfully.";
    return true;
}

void SQLiteDatabase::disconnect() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "SQLite database connection closed.";
    }
}

bool SQLiteDatabase::isConnected() const {
    return db.isOpen();
}
