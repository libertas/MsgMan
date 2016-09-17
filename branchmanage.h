#ifndef BRANCHMANAGE_H
#define BRANCHMANAGE_H

#include "user.h"
#include <QWidget>

namespace Ui {
class BranchManage;
}

class BranchManage : public QWidget
{
    Q_OBJECT

public:
    explicit BranchManage(User *u);
    ~BranchManage();

private:
    Ui::BranchManage *ui;
    User *user;

public slots:
    void onOpenClilcked();
    void onSaveClicked();
};

#endif // BRANCHMANAGE_H
