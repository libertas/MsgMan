#ifndef GOODS_H
#define GOODS_H

#include <QSqlDatabase>
#include <QtCore>


class Good
{
public:
    static bool Init();
    static bool End();
    static QSharedPointer<Good> CreateById(long id);
    static bool Modify(const QList<Good> &goods);
    static QSharedPointer<QList<Good>> getGoods();

    Good(long id, QString name, long price);

    long getId() const;
    QString getName() const;
    long getPrice() const;

private:
    static QSqlDatabase db;
    static bool initialized;

    long id;
    QString name;
    long price;
};

#endif // GOODS_H
