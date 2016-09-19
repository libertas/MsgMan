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
    explicit BranchManage(QSharedPointer<User> u);
    ~BranchManage();

private:
    Ui::BranchManage *ui;
    QSharedPointer<User> user;

public slots:
    void onOpenClicked();
    void onSaveClicked();
};

#endif // BRANCHMANAGE_H
