#ifndef MSGMAN_H
#define MSGMAN_H

#include <QtCore>

class MsgMan
{
public:
    MsgMan(QString db_filename);

    QVector<QPair<QString, QString>> *searchByKey(QString keyword);

    bool insert(QString keyword, QString value);

    bool deleteByKey(QString keyword);
};

#endif // MSGMAN_H
