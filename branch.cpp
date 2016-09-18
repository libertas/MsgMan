#include "branch.h"
#include <assert.h>
#include <QSqlQuery>
#include <QVariantList>


QSqlDatabase Branch::db;
bool Branch::initialized;

bool Branch::Init()
{
    assert(!Branch::initialized);
    Branch::db = QSqlDatabase::addDatabase("QSQLITE", "connBranch");
    Branch::db.setDatabaseName("office.db");
    Branch::initialized = true;

    Branch::db.open();

    QSqlQuery query("", Branch::db);
    query.exec("CREATE TABLE IF NOT EXISTS branches (id, name, addr)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_branch_id ON branches (id)");

    Branch::db.commit();
    Branch::db.close();

    return true;
}

bool Branch::End()
{
    assert(Branch::initialized);

    QSqlDatabase::removeDatabase(Branch::db.connectionName());

    Branch::initialized = false;

    return true;
}

Branch *Branch::CreateById(long id)
{
    assert(Branch::initialized);

    QString name, addr;
    QList<Seller> sellers;

    Branch::db.open();
    QSqlQuery query("", Branch::db);

    query.prepare("SELECT * FROM branches WHERE id=?");
    query.addBindValue(QString::number(id, 10));
    if(query.exec() && query.next()) {
        name = query.value(1).toString();
        addr = query.value(2).toString();
    }

    Branch::db.close();

    Branch *b = new Branch(id, name, addr, sellers);
    return b;
}

Branch::Branch(long id, QString name, QString addr, QList<Seller> sellers)
{
    this->id = id;
    this->name = name;
    this->addr = addr;
    this->sellers = sellers;
}

bool Branch::addSeller(Seller *s)
{
    int index = this->sellers.indexOf(*s);
    if(index >= 0) {
        this->sellers.replace(index, *s);
    } else {
        this->sellers.append(*s);
    }

    return true;
}

bool Branch::removeSeller(Seller *s)
{
    return bool(this->sellers.removeAll(*s));
}

bool Branch::replaceSeller(Seller *s)
{
    int index = this->sellers.indexOf(*s);
    if(index >= 0) {
        Seller s1 = this->sellers.at(index);

        this->removeSeller(&s1);

        s1.replace(s);

        this->addSeller(&s1);
    } else {
        this->sellers.append(*s);
    }

    return true;
}

bool Branch::save()
{
    assert(Branch::initialized);

    Branch::db.open();

    QSqlQuery query("", Branch::db);

    query.prepare("REPLACE INTO branches VALUES (?, ?, ?)");
    query.addBindValue(QString::number(this->id, 10));
    query.addBindValue(this->name);
    query.addBindValue(this->addr);
    query.exec();

    Branch::db.commit();

    Branch::db.close();

    return true;
}

QString Branch::getName()
{
    return this->name;
}

QString Branch::getAddr()
{
    return this->addr;
}

bool Branch::isValid()
{
    if(this->name.isEmpty() && this->addr.isEmpty()) {
        return false;
    } else {
        return true;
    }
}
