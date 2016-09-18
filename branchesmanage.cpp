#include "branch.h"
#include "branchesmanage.h"
#include "ui_branchesmanage.h"

BranchesManage::BranchesManage(User *u) :
    QWidget(0),
    ui(new Ui::BranchesManage)
{
    ui->setupUi(this);
    this->user = u;

    if(!this->user->getIsRoot()) {
        ui->addButton->hide();
        ui->deleteButton->hide();
        ui->applyButton->hide();

        this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    QList<Branch> *branches = Branch::getBranches();
    long row = 0;
    for(QList<Branch>::Iterator iter = branches->begin(); iter != branches->end(); iter++) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(branches->at(row).getId(), 10)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(branches->at(row).getName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(branches->at(row).getAddr()));

        row++;
    }
}

BranchesManage::~BranchesManage()
{
    delete ui;
}

void BranchesManage::onApplyClicked()
{
    QList<Branch> branches;

    for(long row = 0; row != ui->tableWidget->rowCount(); row++) {
        branches.append(Branch(ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toInt(),
                               ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString(),
                               ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toString(),
                               QList<Seller>()));
    }
    Branch::Modify(&branches);
}

void BranchesManage::onResetClicked()
{
    BranchesManage *bm = new BranchesManage(this->user);
    this->close();
    bm->show();
}

void BranchesManage::onAddClicked()
{
    if(this->user->getIsRoot()) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString("name")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString("addr")));
    }
}

void BranchesManage::onDeleteClicked()
{
    if(this->user->getIsRoot()) {
        QList<QTableWidgetSelectionRange> ranges = ui->tableWidget->selectedRanges();
        for(long i = ranges.count() - 1; i >= 0; i--) {
            long topRow = ranges.at(i).topRow();
            long bottomRow = ranges.at(i).bottomRow();
            for(long j = bottomRow; j >= topRow; j--){
                ui->tableWidget->removeRow(j);
            }
        }
    }
}
