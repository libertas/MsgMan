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
    query.exec("CREATE TABLE IF NOT EXISTS sellers (id, name, age, sex, branchId, basicSalary, percentage)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_seller_id ON sellers (id)");

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
    int basicSalary;
    double percentage;

    Seller::db.open();
    QSqlQuery query("", Seller::db);

    query.prepare("SELECT * FROM sellers WHERE id=?");
    query.addBindValue(QString::number(id, 10));
    if(query.exec() && query.next()) {
        name = query.value(1).toString();
        age = query.value(2).toInt();
        sex = query.value(3).toBool();
        branchId = query.value(4).toInt();
        basicSalary = query.value(5).toInt();
        percentage = query.value(6).toDouble();
    }

    Seller::db.close();

    Seller *s = new Seller(id, name, age, sex, branchId);
    s->setBasicSalary(basicSalary);
    s->setPercentage(percentage);
    return s;
}

bool Seller::Modify(QList<Seller> *sellers)
{
    assert(Seller::initialized);
    Seller::db.open();
    QSqlQuery query("", Seller::db);

    query.prepare("DELETE FROM sellers");
    query.exec();

    for(QList<Seller>::Iterator iter = sellers->begin(); iter != sellers->end(); iter++) {
        query.prepare("REPLACE INTO sellers VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(QString::number(iter->getId(), 10));
        query.addBindValue(iter->getName());
        query.addBindValue(iter->getAge());
        query.addBindValue(iter->getSex());
        query.addBindValue(QString::number(iter->getBranchId(), 10));
        query.addBindValue(iter->getBasicSalary());
        query.addBindValue(iter->getPercentage());
        assert(query.exec());
    }

    Seller::db.commit();
    Seller::db.close();

    return true;
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

void Seller::setBasicSalary(int basicSalary)
{
    this->basicSalary = basicSalary;
}

void Seller::setPercentage(double percentage)
{
    this->percentage = percentage;
}

QList<Seller> *Seller::getSellers()
{
    QList<Seller> *sellers = new QList<Seller>;

    Seller::db.open();

    QSqlQuery query("", Seller::db);

    query.prepare("SELECT * FROM sellers");
    query.exec();
    while(query.next()) {
        Seller seller = Seller(query.value(0).toInt(),
                               query.value(1).toString(),
                               query.value(2).toInt(),
                               query.value(3).toBool(),
                               query.value(4).toInt());
        seller.setBasicSalary(query.value(5).toInt());
        seller.setPercentage(query.value(6).toDouble());
        sellers->append(seller);
    }

    Seller::db.close();

    return sellers;
}

QSqlDatabase Seller::getDb()
{
    return Seller::db;
}

long Seller::getId() const
{
    return this->id;
}

QString Seller::getName() const
{
    return this->name;
}

short Seller::getAge() const
{
    return this->age;
}

bool Seller::getSex() const
{
    return this->sex;
}

long Seller::getBranchId() const
{
    return this->branchId;
}

int Seller::getBasicSalary() const
{
    return this->basicSalary;
}

double Seller::getPercentage() const
{
    return this->percentage;
}

bool Seller::operator ==(Seller another)
{
    if(this->id == another.id) {
        return true;
    } else {
        return false;
    }
}
