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
    Branch *b = Branch::CreateById(id);

    ui->nameEdit->setText(b->getName());
    ui->addrEdit->setText(b->getAddr());
}

void BranchManage::onSaveClicked()
{
    long id = ui->idEdit->text().toLong();
    QString name = ui->nameEdit->text();
    QString addr = ui->addrEdit->text();
    QList<Seller> sellers;

    Branch b(id, name, addr, sellers);
    b.save();
}
