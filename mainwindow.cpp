#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermanage.h"


MainWindow::MainWindow(User *u) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->user = user;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUserClicked()
{
    UserManage *um = new UserManage();
    um->show();
}

void MainWindow::onBranchClicked()
{
}

void MainWindow::onSellClicked()
{
}

void MainWindow::onSearchClicked()
{
}

void MainWindow::onSalaryClicked()
{
}
