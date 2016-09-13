#include "msgman.h"
#include <iostream>


MsgMan::MsgMan(QString db_filename)
{
    std::cout<<"Initializing MsgMan,db:"<<db_filename.toStdString()<<std::endl;
}

QVector<QPair<QString, QString>> *MsgMan::SearchByKey(QString keyword)
{
    QVector<QPair<QString, QString>> *result = new QVector<QPair<QString, QString>>;

    return result;
}

bool MsgMan::Insert(QString keyword, QString value)
{
    return true;
}

bool MsgMan::Delete(QString keyword)
{
    return true;
}
