#ifndef USER_H
#define USER_H

#include <QtCore>
#include <QSqlDatabase>


class User
{
public:
    static bool Init();
    static bool End();
    static QSharedPointer<QList<User>> getUsers();
    static bool noRootUser();
    static bool Modify(const QList<User> &users);

    // Create a new user
    User(QString name, QString password, bool isRoot);

    // Create a user from the database
    User(QString name, QString password);

    bool operator ==(User another);

    QString getName() const;
    QString getPassword() const;
    bool getIsRoot() const;
    bool save();
    void copy(const User &u);

private:
    static QSqlDatabase db;
    static bool initialized;
    QString name;
    QString password;
    bool isRoot;
};

#endif // USER_H
