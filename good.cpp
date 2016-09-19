#include "good.h"
#include <QSqlQuery>
#include <assert.h>


QSqlDatabase Good::db;
bool Good::initialized;

bool Good::Init()
{
    assert(!Good::initialized);
    Good::db = QSqlDatabase::addDatabase("QSQLITE", "connGood");
    Good::db.setDatabaseName("office.db");
    Good::initialized = true;

    Good::db.open();

    QSqlQuery query("", Good::db);
    query.exec("CREATE TABLE IF NOT EXISTS goods (id, name, price)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_good_id ON goods (id)");

    Good::db.commit();
    Good::db.close();

    return true;
}

bool Good::End()
{
    assert(Good::initialized);

    QSqlDatabase::removeDatabase(Good::db.connectionName());

    Good::initialized = false;

    return true;
}

Good::Good(long id, QString name, long price)
{
    this->id = id;
    this->name =name;
    this->price = price;
}

long Good::getId() const
{
    return this->id;
}

QString Good::getName() const
{
    return this->name;
}

long Good::getPrice() const
{
    return this->price;
}

QSharedPointer<Good> Good::CreateById(long id)
{
    assert(Good::initialized);
    QString name;
    long price;

    Good::db.open();
    QSqlQuery query("", Good::db);

    query.prepare("SELECT * FROM goods WHERE id=?");
    query.addBindValue(QString::number(id, 10));
    if(query.exec() && query.next()) {
        name = query.value(1).toString();
        price = query.value(2).toInt();
    } else {
        name = "";
        price = 0;
    }

    Good::db.close();

    QSharedPointer<Good> s(new Good(id, name, price));
    return s;
}

bool Good::Modify(const QList<Good> &goods)
{
    assert(Good::initialized);
    Good::db.open();
    QSqlQuery query("", Good::db);

    query.prepare("DELETE FROM goods");
    query.exec();

    for(QList<Good>::const_iterator iter = goods.begin(); iter != goods.end(); iter++) {
        query.prepare("REPLACE INTO goods VALUES (?, ?, ?)");
        query.addBindValue(QString::number(iter->getId(), 10));
        query.addBindValue(iter->getName());
        query.addBindValue(QString::number(iter->getPrice(), 10));
        assert(query.exec());
    }

    Good::db.commit();
    Good::db.close();

    return true;
}

QSharedPointer<QList<Good> > Good::getGoods()
{
    QSharedPointer<QList<Good>> goods(new QList<Good>);

    Good::db.open();

    QSqlQuery query("", Good::db);

    query.prepare("SELECT * FROM goods");
    query.exec();
    while(query.next()) {
        Good good = Good(query.value(0).toInt(),
                         query.value(1).toString(),
                         query.value(2).toInt());
        goods->append(good);
    }

    Good::db.close();

    return goods;
}
