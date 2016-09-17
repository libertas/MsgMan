#ifndef BRANCH_H
#define BRANCH_H

#include "seller.h"
#include <QtCore>

class Branch
{
public:
    Branch(long id);

    bool addSeller(Seller *s);
    bool removeSeller(Seller *s);
    bool replaceSeller(Seller *s);

private:
    long id;
    QList<Seller> sellers;
};

#endif // BRANCH_H
