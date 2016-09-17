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

    Branch(long id);

    bool addSeller(Seller *s);
    bool removeSeller(Seller *s);
    bool replaceSeller(Seller *s);

private:
    static QSqlDatabase db;
    static bool initialized;

    long id;
    QList<Seller> sellers;
};

#endif // BRANCH_H
