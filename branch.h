#ifndef BRANCH_H
#define BRANCH_H

#include "seller.h"
#include <QtCore>
#include <QSqlDatabase>

class Branch
{
public:
    static bool Init();
    static bool End();
    static QSharedPointer<Branch> CreateById(long id);
    static QSharedPointer<QList<Branch>> getBranches();
    static bool Modify(const QList<Branch> &branches);

    Branch(long id, QString name, QString addr, QList<Seller> sellers);

    bool addSeller(const Seller &s);
    bool removeSeller(const Seller &s);
    bool replaceSeller(const Seller &s);
    bool save();

    long getId() const;
    QString getName() const;
    QString getAddr() const;
    QSharedPointer<QList<Seller>> getSellers();

private:
    static QSqlDatabase db;
    static bool initialized;

    bool isValid();

    long id;
    QString name;
    QString addr;
    QList<Seller> sellers;
};

#endif // BRANCH_H
