#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(bool isRoot) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUserClicked()
{
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
