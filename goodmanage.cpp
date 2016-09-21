#include "good.h"
#include "goodmanage.h"
#include "ui_goodmanage.h"


GoodManage::GoodManage(QSharedPointer<User> u) :
    QWidget(0),
    ui(new Ui::GoodManage)
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
    QSharedPointer<QList<Good>> goods = Good::getGoods();
    for(QList<Good>::Iterator iter = goods->begin(); iter != goods->end(); iter++) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(goods->at(row).getId(), 10)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(goods->at(row).getName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(goods->at(row).getPrice())));

        row++;
    }
}

GoodManage::~GoodManage()
{
    delete ui;
}

void GoodManage::onApplyClicked()
{
    if(this->user->getIsRoot()) {
            QList<Good> goods;

            for(long row = 0; row != ui->tableWidget->rowCount(); row++) {
                Good good = Good(ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toInt(),
                                       ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString(),
                                       ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toInt());
                goods.append(good);
            }
            Good::Modify(goods);
        }
}

void GoodManage::onResetClicked()
{
    GoodManage *gm = new GoodManage(this->user);
    this->close();
    gm->show();
}

void GoodManage::onAddClicked()
{
    if(this->user->getIsRoot()) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString("name")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString("0")));
    }
}

void GoodManage::onDeleteClicked()
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
