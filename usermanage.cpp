#include "usermanage.h"
#include "ui_usermanage.h"
#include <iostream>

UserManage::UserManage(User *u) :
    QMainWindow(0),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    this->user = u;
    if(this->user->getIsRoot()) {
        QList<User> *users = User::getUsers();
        unsigned long row = 0;
        for(QList<User>::Iterator iter = users->begin(); iter != users->end(); iter++) {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(users->at(row).getName()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(users->at(row).getPassword()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString(int(users->at(row).getIsRoot()) + '0')));

            row++;
        }
    }
}

UserManage::~UserManage()
{
    delete ui;
}
