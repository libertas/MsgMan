#include "seller.h"

Seller::Seller(long id, QString name, short age, bool sex)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->sex = sex;
}

void Seller::replace(Seller *s)
{
    this->id = s->id;
    this->name = s->name;
    this->age = s->age;
    this->sex = s->sex;
}

void Seller::copy(Seller *s)
{
    this->replace(s);
    this->basicSalary = s->basicSalary;
    this->percentage = s->percentage;
}

bool Seller::operator ==(Seller another)
{
    if(this->id == another.id) {
        return true;
    } else {
        return false;
    }
}
