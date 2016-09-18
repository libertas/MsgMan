#include "seller.h"
#include "sellermanage.h"
#include "ui_sellermanage.h"

SellerManage::SellerManage(User *u) :
    QWidget(0),
    ui(new Ui::SellerManage)
{
    ui->setupUi(this);
    this->user = u;

    if(!this->user->getIsRoot()) {
        this->ui->addButton->hide();
        this->ui->deleteButton->hide();
        this->ui->applyButton->hide();
        this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    long row = 0;
    QList<Seller> *sellers = Seller::getSellers();
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

SellerManage::~SellerManage()
{
    delete ui;
}

void SellerManage::onApplyClicked()
{
    if(this->user->getIsRoot()) {
        QList<Seller> sellers;

        for(long row = 0; row != ui->tableWidget->rowCount(); row++) {
            Seller seller = Seller(ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toInt(),
                                   ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString(),
                                   ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toInt(),
                                   ui->tableWidget->item(row, 3)->data(Qt::DisplayRole).toBool(),
                                   ui->tableWidget->item(row, 4)->data(Qt::DisplayRole).toInt());
            seller.setBasicSalary(ui->tableWidget->item(row, 5)->data(Qt::DisplayRole).toInt());
            seller.setPercentage(ui->tableWidget->item(row, 6)->data(Qt::DisplayRole).toDouble());
            sellers.append(seller);
        }
        Seller::Modify(&sellers);
    }
}

void SellerManage::onResetClicked()
{
    SellerManage *sm = new SellerManage(this->user);
    this->close();
    sm->show();
}

void SellerManage::onAddClicked()
{
    if(this->user->getIsRoot()) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString("name")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString("1")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 6, new QTableWidgetItem(QString("0")));
    }
}

void SellerManage::onDeleteClicked()
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
