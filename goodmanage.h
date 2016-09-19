#ifndef GOODMANAGE_H
#define GOODMANAGE_H

#include "user.h"
#include <QWidget>

namespace Ui {
class GoodManage;
}

class GoodManage : public QWidget
{
    Q_OBJECT

public:
    explicit GoodManage(QSharedPointer<User> u);
    ~GoodManage();

private:
    Ui::GoodManage *ui;
    QSharedPointer<User> user;

public slots:
    void onApplyClicked();
    void onResetClicked();
    void onAddClicked();
    void onDeleteClicked();
};

#endif // GOODMANAGE_H
