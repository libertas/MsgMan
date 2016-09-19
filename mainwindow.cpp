#include "branchesmanage.h"
#include "branchmanage.h"
#include "mainwindow.h"
#include "sellermanage.h"
#include "ui_mainwindow.h"
#include "usermanage.h"


MainWindow::MainWindow(QSharedPointer<User> u) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->user = u;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUserClicked()
{
    UserManage *um = new UserManage(this->user);
    um->show();
}

void MainWindow::onBranchClicked()
{
    BranchManage *bm = new BranchManage(this->user);
    bm->show();
}

void MainWindow::onBranchesClicked()
{
    BranchesManage *bm = new BranchesManage(this->user);
    bm->show();
}

void MainWindow::onSellClicked()
{
}

void MainWindow::onSearchClicked()
{
}

void MainWindow::onSellerClicked()
{
    SellerManage *sm = new SellerManage(this->user);
    sm->show();
}
