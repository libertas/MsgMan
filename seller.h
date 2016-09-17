#ifndef SELLER_H
#define SELLER_H

#include <QtCore>


class Seller
{
public:
    Seller(long id, QString name, short age, bool sex);

    void replace(Seller *s);
    void copy(Seller *s);

    bool operator ==(Seller another);

private:
    long id;
    QString name;
    short age;
    bool sex;

    int basicSalary;
    double percentage;
};

#endif // SELLER_H
