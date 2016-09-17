#include "branch.h"
#include <assert.h>
#include <QSqlQuery>


QSqlDatabase Branch::db;
bool Branch::initialized;

bool Branch::Init()
{
    assert(!Branch::initialized);
    Branch::db = QSqlDatabase::addDatabase("QSQLITE", "connSQLite");
    Branch::db.setDatabaseName("office.db");
    Branch::initialized = true;

    Branch::db.open();

    QSqlQuery query("", Branch::db);
    query.exec("CREATE TABLE IF NOT EXISTS branches (id, name, addr)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_id ON users (id)");

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

Branch::Branch(long id)
{
    this->id = id;
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
