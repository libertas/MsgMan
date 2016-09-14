#ifndef MSGMAN_H
#define MSGMAN_H

#include <QtCore>

class MsgMan
{
public:
    MsgMan(bool isRoot);

    QVector<QPair<QString, QString>> *searchByKey(QString keyword);

    bool insert(QString keyword, QString value);

    bool deleteByKey(QString keyword);

private:
    bool isRoot;
};

#endif // MSGMAN_H
