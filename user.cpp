#include "user.h"
#include "assert.h"

QSqlDatabase User::db;
bool User::initialized;

bool User::Init()
{
    User::db = QSqlDatabase::addDatabase("QSQLITE", "connSQLite");
    User::db.setDatabaseName("password.db");
    User::initialized = true;

    return true;
}

User::User(QString name, QString password, bool isRoot)
{
    assert(User::initialized);
    this->name = name;
    this->password = password;
    this->isRoot = isRoot;
}

bool User::checkUser()
{
    if(User::noUser()) {
        return false;
    }

    return true;
}

bool User::noUser()
{
    assert(User::initialized);
    if(User::db.open() == false) {
        return true;
    }

    return false;
}
