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
    query.exec("CREATE TABLE IF NOT EXISTS sellers (id, name, age, sex, basicSalary, percentage, branchId)");
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

Seller *Seller::CreateById(long id)
{
    assert(Seller::initialized);
    QString name;
    short age;
    bool sex;
    long branchId;

    Seller::db.open();
    QSqlQuery query("", Seller::db);

    query.prepare("SELECT * FROM sellers WHERE id=?");
    query.addBindValue(QString::number(id, 10));
    if(query.exec() && query.next()) {
        name = query.value(1).toString();
        age = query.value(2).toInt();
        sex = query.value(3).toBool();
        branchId = query.value(4).toInt();
    }

    Seller::db.close();

    Seller *s = new Seller(id, name, age, sex, branchId);
    return s;
}

Seller::Seller(long id, QString name, short age, bool sex, long branchId)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->sex = sex;
    this->branchId = branchId;
}

void Seller::replace(Seller *s)
{
    this->id = s->id;
    this->name = s->name;
    this->age = s->age;
    this->sex = s->sex;
    this->branchId = branchId;
}

void Seller::copy(Seller *s)
{
    this->replace(s);
    this->basicSalary = s->basicSalary;
    this->percentage = s->percentage;
}

bool Seller::save()
{
    Seller::db.open();

    QSqlQuery query("", Seller::db);

    query.prepare("REPLACE INTO sellers VALUES(?, ?, ?, ?, ?)");
    query.addBindValue(QString::number(this->id));
    query.addBindValue(this->name);
    query.addBindValue(this->age);
    query.addBindValue(this->sex);
    query.addBindValue(QString::number(this->branchId));
    query.exec();

    Seller::db.commit();

    Seller::db.close();

    return true;
}

bool Seller::operator ==(Seller another)
{
    if(this->id == another.id) {
        return true;
    } else {
        return false;
    }
}
