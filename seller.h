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
    static bool Modify(QList<Seller> *sellers);
    static QList<Seller> *getSellers();

    Seller(long id, QString name, short age, bool sex, long branchId);

    void replace(Seller *s);
    void copy(Seller *s);
    bool save();
    void setBasicSalary(int basicSalary);
    void setPercentage(double percentage);

    long getId() const;
    QString getName() const;
    short getAge() const;
    bool getSex() const;
    long getBranchId() const;
    int getBasicSalary() const;
    double getPercentage() const;

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
