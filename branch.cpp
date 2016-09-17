#include "branch.h"

Branch::Branch(long id)
{
    this->id = id;
}

bool Branch::addSeller(Seller *s)
{
    int index = this->sellers.indexOf(*s);
    if(index >= 0) {
        this->sellers.replace(index, *s);
    } else {
        this->sellers.append(*s);
    }

    return true;
}

bool Branch::removeSeller(Seller *s)
{
    return bool(this->sellers.removeAll(*s));
}

bool Branch::replaceSeller(Seller *s)
{
    int index = this->sellers.indexOf(*s);
    if(index >= 0) {
        Seller s1 = this->sellers.at(index);

        this->removeSeller(&s1);

        s1.replace(s);

        this->addSeller(&s1);
    } else {
        this->sellers.append(*s);
    }

    return true;
}
