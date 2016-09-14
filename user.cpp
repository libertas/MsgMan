#include "user.h"
#include "assert.h"
#include <QSqlQuery>

QSqlDatabase User::db;
bool User::initialized;

bool User::Init()
{
    User::db = QSqlDatabase::addDatabase("QSQLITE", "connSQLite");
    User::db.setDatabaseName("password.db");
    User::initialized = true;
    db.open();
    QSqlQuery query("", db);
    query.exec("CREATE TABLE IF NOT EXISTS users (username, password, isRoot)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_username ON favs (username)");
    db.commit();
    db.close();

    return true;
}

User::User(QString name, QString password, bool isRoot)
{
    assert(User::initialized);
    this->name = name;
    this->password = password;
    this->isRoot = isRoot;
}

User::User(QString name, QString password)
{
    assert(User::initialized);
    this->name = name;
    this->password = password;

    // Read user data from the database
}
