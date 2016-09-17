#include "branch.h"
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

void BranchManage::onOpenClicked()
{
    long id = ui->idEdit->text().toLong();
    Branch *b = new Branch(id);
    ui->nameEdit->setText(b->getName());
}

void BranchManage::onSaveClicked()
{

}
