#include "branch.h"
#include "seller.h"
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

    Seller::getDb().open();
    query = QSqlQuery("", Seller::getDb());

    query.prepare("SELECT * FROM sellers WHERE branchId=?");
    query.addBindValue(QString::number(id, 10));
    query.exec();
    while(query.next()) {
        Seller seller = Seller(query.value(0).toInt(),
                               query.value(1).toString(),
                               query.value(2).toInt(),
                               query.value(3).toBool(),
                               query.value(4).toInt());
        seller.setBasicSalary(query.value(5).toInt());
        seller.setPercentage(query.value(6).toDouble());
        sellers.append(seller);
    }

    Seller::getDb().close();

    Branch *b = new Branch(id, name, addr, sellers);
    return b;
}

QList<Branch> *Branch::getBranches()
{
    QList<Branch> *branches = new QList<Branch>;
    QList<long> ids;

    Branch::db.open();
    QSqlQuery query("", Branch::db);

    query.prepare("SELECT * FROM branches");
    query.exec();
    while(query.next()) {
        ids.append(query.value(0).toInt());
    }

    Branch::db.close();

    for(QList<long>::Iterator iter = ids.begin(); iter != ids.end(); iter++) {
        branches->append(*Branch::CreateById(*iter));
    }

    return branches;
}

bool Branch::Modify(QList<Branch> *branches)
{
    assert(Branch::initialized);
    Branch::db.open();
    QSqlQuery query("", Branch::db);

    query.prepare("DELETE FROM branches");
    query.exec();

    for(QList<Branch>::Iterator iter = branches->begin(); iter != branches->end(); iter++) {
        query.prepare("REPLACE INTO branches VALUES (?, ?, ?)");
        query.addBindValue(QString::number(iter->getId(), 10));
        query.addBindValue(iter->getName());
        query.addBindValue(iter->getAddr());
        assert(query.exec());
    }

    Branch::db.commit();
    Branch::db.close();
    return true;
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

long Branch::getId() const
{
    return this->id;
}

QString Branch::getName() const
{
    return this->name;
}

QString Branch::getAddr() const
{
    return this->addr;
}

QList<Seller> *Branch::getSellers()
{
    return &sellers;
}

bool Branch::isValid()
{
    if(this->name.isEmpty() && this->addr.isEmpty()) {
        return false;
    } else {
        return true;
    }
}
