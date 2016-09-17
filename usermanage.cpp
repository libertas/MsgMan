#include "mainwindow.h"
#include "usermanage.h"
#include "ui_usermanage.h"

UserManage::UserManage(User *u) :
    QMainWindow(0),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    this->user = u;

    if(this->user->getIsRoot()) {
        QList<User> *users = User::getUsers();
        long row = 0;
        for(QList<User>::Iterator iter = users->begin(); iter != users->end(); iter++) {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(users->at(row).getName()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(users->at(row).getPassword()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString(int(users->at(row).getIsRoot()) + '0')));

            row++;
        }
    } else {
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(this->user->getName()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(this->user->getPassword()));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString(int(this->user->getIsRoot()) + '0')));
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
        User::Modify(&users);
    } else {
        User *u = new User(this->user->getName(),
                           ui->tableWidget->item(0, 1)->data(Qt::DisplayRole).toString(),
                           false);
        this->user->copy(u);
        this->user->save();
    }
}

void UserManage::onResetClicked()
{

}
