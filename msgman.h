#ifndef MSGMAN_H
#define MSGMAN_H

#include <QtCore>

class MsgMan
{
public:
    MsgMan(QString db_filename);

    QVector<QPair<QString, QString>> *SearchByKey(QString keyword);

    bool Insert(QString keyword, QString value);

    bool Delete(QString keyword);
};

#endif // MSGMAN_H
