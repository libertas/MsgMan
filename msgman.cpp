#include "msgman.h"
#include <iostream>


MsgMan::MsgMan(bool isRoot)
{
    std::cout<<"Initializing MsgMan,"<<isRoot<<std::endl;
    this->isRoot = isRoot;
}

QVector<QPair<QString, QString>> *MsgMan::searchByKey(QString keyword)
{
    QVector<QPair<QString, QString>> *result = new QVector<QPair<QString, QString>>;

    std::cout<<"Searching for "<<keyword.toStdString()<<std::endl;

    return result;
}

bool MsgMan::insert(QString keyword, QString value)
{
    if(this->isRoot) {
        return true;
    } else {
        return false;
    }

}

bool MsgMan::deleteByKey(QString keyword)
{
    if(this->isRoot) {
        return true;
    } else {
        return false;
    }
}
