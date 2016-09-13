#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    msgman = new MsgMan("abc");
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
