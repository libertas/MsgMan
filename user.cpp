#include "user.h"
#include "assert.h"
#include <QSqlQuery>

QSqlDatabase User::db;
bool User::initialized;

bool User::Init()
{
    assert(!User::initialized);
    User::db = QSqlDatabase::addDatabase("QSQLITE", "connSQLite");
    User::db.setDatabaseName("password.db");
    User::initialized = true;

    User::db.open();

    QSqlQuery query("", User::db);
    query.exec("CREATE TABLE IF NOT EXISTS users (username, password, isRoot)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_username ON users (username)");

    User::db.commit();
    User::db.close();

    return true;
}

bool User::End()
{
    assert(User::initialized);

    QSqlDatabase::removeDatabase(User::db.connectionName());

    User::initialized = false;

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
    assert(User::initialized);
    QList<User> *users = User::getUsers();
    for(QList<User>::Iterator iter = users->begin(); iter != users->end(); iter++) {
        if(iter->isRoot == true) {
            return false;
        }
    }
    return true;
}

bool User::Modify(QList<User> *users)
{
    assert(User::initialized);
    User::db.open();
    QSqlQuery query("", User::db);

    query.prepare("DELETE FROM users");
    query.exec();

    for(QList<User>::Iterator iter = users->begin(); iter != users->end(); iter++) {
        query.prepare("REPLACE INTO users VALUES (?, ?, ?)");
        query.addBindValue(iter->getName());
        query.addBindValue(iter->getPassword());
        query.addBindValue(iter->getIsRoot());
        assert(query.exec());
    }

    User::db.commit();
    User::db.close();
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
    User::db.open();
    QSqlQuery query("", User::db);
    query.prepare("SELECT * FROM users WHERE username=?");
    query.addBindValue(name);
    if(query.exec() && query.next()) {
        this->isRoot = query.value(2).toBool();
    } else {
        this->isRoot = 0;
    }

    User::db.close();
}

bool User::operator ==(User another)
{
    assert(User::initialized);

    if(this->name == another.name
            && this->password == another.password) {
        return true;
    } else {
        return false;
    }
}

QString User::getName() const
{
    assert(User::initialized);

    return this->name;
}

QString User::getPassword() const
{
    assert(User::initialized);

    return this->password;
}

bool User::getIsRoot() const
{
    assert(User::initialized);

    return this->isRoot;
}

bool User::save()
{
    assert(User::initialized);

    User::db.open();
    QSqlQuery query("", User::db);
    query.prepare("REPLACE INTO users VALUES (?, ?, ?)");
    query.addBindValue(this->name);
    query.addBindValue(this->password);
    query.addBindValue(this->isRoot);
    assert(query.exec());
    User::db.commit();
    User::db.close();

    return true;
}

void User::copy(User *u)
{
    assert(User::initialized);

    this->name = u->getName();
    this->password = u->getPassword();
    this->isRoot = u->getIsRoot();
}
