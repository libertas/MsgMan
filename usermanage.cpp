#include "mainwindow.h"
#include "usermanage.h"
#include "ui_usermanage.h"

UserManage::UserManage(QSharedPointer<User> u) :
    QMainWindow(0),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    this->user = u;

    if(this->user->getIsRoot()) {
        QSharedPointer<QList<User>> users = User::getUsers();
        long row = 0;
        for(QList<User>::Iterator iter = users->begin(); iter != users->end(); iter++) {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(users->at(row).getName()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(users->at(row).getPassword()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString(int(users->at(row).getIsRoot()) + '0')));

            row++;
        }
    } else {
        ui->addButton->hide();
        ui->applyButton->hide();
        ui->deleteButton->hide();

        ui->tableWidget->setRowCount(1);

        QTableWidgetItem *itemName = new QTableWidgetItem(this->user->getName());
        itemName->setFlags(itemName->flags() & ~Qt::ItemIsEditable);

        QTableWidgetItem *itemPassword = new QTableWidgetItem(this->user->getPassword());

        QTableWidgetItem *itemIsRoot = new QTableWidgetItem(QString(int(this->user->getIsRoot()) + '0'));
        itemIsRoot->setFlags(itemIsRoot->flags() & ~Qt::ItemIsEditable);

        ui->tableWidget->setItem(0, 0, itemName);
        ui->tableWidget->setItem(0, 1, itemPassword);
        ui->tableWidget->setItem(0, 2, itemIsRoot);

        delete itemName;
        delete itemPassword;
        delete itemIsRoot;
    }
}

UserManage::~UserManage()
{
    delete ui;
}

void UserManage::onApplyClicked()
{
    if(this->user->getIsRoot()) {
        QList<User> users;

        for(long row = 0; row != ui->tableWidget->rowCount(); row++) {
            users.append(User(ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toString(),
                              ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString(),
                              ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toBool()));
        }
        User::Modify(users);
    } else {
        QSharedPointer<User> u(new User(this->user->getName(),
                                   ui->tableWidget->item(0, 1)->data(Qt::DisplayRole).toString(),
                                   false));
        this->user->copy(*u);
        this->user->save();
    }
}

void UserManage::onResetClicked()
{
    UserManage *um = new UserManage(this->user);
    this->close();
    um->show();
}

void UserManage::onAddClicked()
{
    if(this->user->getIsRoot()) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString("username")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString("password")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString("0")));
    }
}

void UserManage::onDeleteClicked()
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
