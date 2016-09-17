#ifndef USERMANAGE_H
#define USERMANAGE_H

#include "user.h"
#include <QMainWindow>

namespace Ui {
class UserManage;
}

class UserManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserManage(User *u);
    ~UserManage();

private:
    Ui::UserManage *ui;
    User *user;

public slots:
    void onApplyClicked();
    void onResetClicked();
    void onAddClicked();
    void onDeleteClicked();
};

#endif // USERMANAGE_H
