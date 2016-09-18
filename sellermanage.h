#ifndef SELLERMANAGE_H
#define SELLERMANAGE_H

#include "user.h"
#include <QWidget>

namespace Ui {
class SellerManage;
}

class SellerManage : public QWidget
{
    Q_OBJECT

public:
    explicit SellerManage(User *u);
    ~SellerManage();

private:
    Ui::SellerManage *ui;
    User *user;

public slots:
    void onApplyClicked();
    void onResetClicked();
    void onAddClicked();
    void onDeleteClicked();
};

#endif // SELLERMANAGE_H
