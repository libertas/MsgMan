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
    static Branch *CreateById(long id);

    Branch(long id, QString name, QString addr, QList<Seller> sellers);

    bool addSeller(Seller *s);
    bool removeSeller(Seller *s);
    bool replaceSeller(Seller *s);
    bool save();

    QString getName();
    QString getAddr();
    QList<Seller> *getSellers();

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
