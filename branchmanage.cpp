#include "branchmanage.h"
#include "ui_branchmanage.h"

BranchManage::BranchManage(User *u) :
    QWidget(0),
    ui(new Ui::BranchManage)
{
    ui->setupUi(this);
    this->user = u;
}

BranchManage::~BranchManage()
{
    delete ui;
}

void BranchManage::onOpenClilcked()
{

}

void BranchManage::onSaveClicked()
{

}
