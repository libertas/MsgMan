#include "seller.h"
#include <assert.h>
#include <QSqlQuery>


QSqlDatabase Seller::db;
bool Seller::initialized;

bool Seller::Init()
{
    assert(!Seller::initialized);
    Seller::db = QSqlDatabase::addDatabase("QSQLITE", "connSeller");
    Seller::db.setDatabaseName("office.db");
    Seller::initialized = true;

    Seller::db.open();

    QSqlQuery query("", Seller::db);
    query.exec("CREATE TABLE IF NOT EXISTS sellers (id, name, age, sex, basicSalary, percentage)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_id ON sellers (id)");

    Seller::db.commit();
    Seller::db.close();

    return true;
}

bool Seller::End()
{
    assert(Seller::initialized);

    QSqlDatabase::removeDatabase(Seller::db.connectionName());

    Seller::initialized = false;

    return true;
}

Seller::Seller(long id, QString name, short age, bool sex)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->sex = sex;
}

void Seller::replace(Seller *s)
{
    this->id = s->id;
    this->name = s->name;
    this->age = s->age;
    this->sex = s->sex;
}

void Seller::copy(Seller *s)
{
    this->replace(s);
    this->basicSalary = s->basicSalary;
    this->percentage = s->percentage;
}

bool Seller::operator ==(Seller another)
{
    if(this->id == another.id) {
        return true;
    } else {
        return false;
    }
}
