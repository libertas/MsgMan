#include "branch.h"
#include "branchmanage.h"
#include "seller.h"
#include "ui_branchmanage.h"

BranchManage::BranchManage(QSharedPointer<User> u) :
    QWidget(0),
    ui(new Ui::BranchManage)
{
    ui->setupUi(this);
    this->user = u;
    if(!this->user->getIsRoot()) {
        ui->nameEdit->setFocusPolicy(Qt::NoFocus);
        ui->addrEdit->setFocusPolicy(Qt::NoFocus);
        ui->saveButton->hide();
    }
}

BranchManage::~BranchManage()
{
    delete ui;
}

void BranchManage::onOpenClicked()
{
    long id = ui->idEdit->text().toLong();
    QSharedPointer<Branch> b = Branch::CreateById(id);

    ui->nameEdit->setText(b->getName());
    ui->addrEdit->setText(b->getAddr());

    long row = 0;
    ui->tableWidget->setRowCount(row);
    QSharedPointer<QList<Seller>> sellers = b->getSellers();

    for(QList<Seller>::Iterator iter = sellers->begin(); iter != sellers->end(); iter++) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(sellers->at(row).getId(), 10)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(sellers->at(row).getName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(sellers->at(row).getAge())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(int(sellers->at(row).getSex())), 10));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(sellers->at(row).getBranchId())));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(sellers->at(row).getBasicSalary())));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(sellers->at(row).getPercentage())));

        row++;
    }
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
