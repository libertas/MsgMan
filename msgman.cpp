#include "msgman.h"
#include <iostream>


MsgMan::MsgMan(QString db_filename)
{
    std::cout<<"Initializing MsgMan,db:"<<db_filename.toStdString()<<std::endl;
}

QVector<QPair<QString, QString>> *MsgMan::searchByKey(QString keyword)
{
    QVector<QPair<QString, QString>> *result = new QVector<QPair<QString, QString>>;

    std::cout<<"Searching for "<<keyword.toStdString()<<std::endl;

    return result;
}

bool MsgMan::insert(QString keyword, QString value)
{
    return true;
}

bool MsgMan::deleteByKey(QString keyword)
{
    return true;
}
