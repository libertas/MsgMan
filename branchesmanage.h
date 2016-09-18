#ifndef BRANCHESMANAGE_H
#define BRANCHESMANAGE_H

#include "user.h"
#include <QWidget>

namespace Ui {
class BranchesManage;
}

class BranchesManage : public QWidget
{
    Q_OBJECT

public:
    explicit BranchesManage(User *u);
    ~BranchesManage();

private:
    Ui::BranchesManage *ui;
    User *user;

public slots:
    void onApplyClicked();
    void onResetClicked();
    void onAddClicked();
    void onDeleteClicked();
};

#endif // BRANCHESMANAGE_H
