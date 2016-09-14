#ifndef USER_H
#define USER_H

#include <QtCore>
#include <QSqlDatabase>


class User
{
public:
    static bool Init();
    User(QString name, QString password, bool isRoot);

    bool checkUser();
    static bool noUser();

private:
    static QSqlDatabase db;
    static bool initialized;
    QString name;
    QString password;
    bool isRoot;
};

#endif // USER_H
