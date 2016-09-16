#ifndef USER_H
#define USER_H

#include <QtCore>
#include <QSqlDatabase>


class User
{
public:
    static bool Init();
    static bool End();
    static QList<User> *getUsers();
    static bool noRootUser();
    static bool Modify(QList<User> *users);

    // Create a new user
    User(QString name, QString password, bool isRoot);

    // Create a user from the database
    User(QString name, QString password);

    bool operator ==(User another);

    QString getName() const;
    QString getPassword() const;
    bool getIsRoot() const;
    bool save();

private:
    static QSqlDatabase db;
    static bool initialized;
    QString name;
    QString password;
    bool isRoot;
};

#endif // USER_H
