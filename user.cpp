#include "user.h"
#include "assert.h"
#include <QSqlQuery>
#include <iostream>

QSqlDatabase User::db;
bool User::initialized;

bool User::Init()
{
    User::db = QSqlDatabase::addDatabase("QSQLITE", "connSQLite");
    User::db.setDatabaseName("password.db");
    User::initialized = true;

    User::db.open();

    QSqlQuery query("", User::db);
    query.exec("CREATE TABLE IF NOT EXISTS users (username, password, isRoot)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_username ON favs (username)");

    User::db.commit();

    User::db.close();

    return true;
}

bool User::End()
{
    assert(User::initialized);

    QSqlDatabase::removeDatabase(User::db.connectionName());

    return true;
}

QList<User> *User::getUsers()
{
    assert(User::initialized);

    QList<User> *users = new QList<User>;

    User::db.open();
    QSqlQuery query("", User::db);

    query.prepare("SELECT * FROM users");
    query.exec();
    while(query.next()) {
        users->append(User(query.value(0).toString(),
                               query.value(1).toString(),
                               query.value(2).toBool()));
    }
    User::db.close();

    return users;
}

bool User::noRootUser()
{
    QList<User> *users = User::getUsers();
    for(QList<User>::Iterator iter = users->begin(); iter != users->end(); iter++) {
        if(iter->isRoot == true) {
            return false;
        }
    }
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

bool User::operator ==(User another)
{
    if(this->name == another.name
            && this->password == another.password) {
        return true;
    } else {
        return false;
    }
}

QString User::getName() const
{
    return this->name;
}

QString User::getPassword() const
{
    return this->password;
}

bool User::getIsRoot() const
{
    return this->isRoot;
}
