#ifndef SELLER_H
#define SELLER_H

#include <QtCore>
#include <QSqlDatabase>


class Seller
{
public:
    static bool Init();
    static bool End();
    static Seller *CreateById(long id);

    Seller(long id, QString name, short age, bool sex, long branchId);

    void replace(Seller *s);
    void copy(Seller *s);
    bool save();

    bool operator ==(Seller another);

private:
    static QSqlDatabase db;
    static bool initialized;

    long id;
    QString name;
    short age;
    bool sex;
    long branchId;

    int basicSalary;
    double percentage;
};

#endif // SELLER_H
