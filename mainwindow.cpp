#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(bool isRoot) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    msgman = new MsgMan(isRoot);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete msgman;
}

void MainWindow::onSearchClicked()
{
    msgman->searchByKey(ui->searchEdit->text());
}
