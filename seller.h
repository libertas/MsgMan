#ifndef SELLER_H
#define SELLER_H

#include <QtCore>
#include <QSqlDatabase>


class Seller
{
public:
    static bool Init();
    static bool End();

    Seller(long id, QString name, short age, bool sex);

    void replace(Seller *s);
    void copy(Seller *s);

    bool operator ==(Seller another);

private:
    static QSqlDatabase db;
    static bool initialized;

    long id;
    QString name;
    short age;
    bool sex;

    int basicSalary;
    double percentage;
};

#endif // SELLER_H
