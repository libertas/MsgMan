#include "logindialog.h"
#include "mainwindow.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->incorrectLabel->hide();

    rootUsers.append(QPair<QString, QString>("root", "root123"));

    users.append(QPair<QString, QString>("user", "user123"));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

#include <iostream>
void LoginDialog::onLogin()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if(rootUsers.indexOf(QPair<QString, QString>(username, password)) >= 0) {
        this->destroy();
        MainWindow *w = new MainWindow(true);
        w->show();
    } else if(users.indexOf(QPair<QString, QString>(username, password)) >= 0) {
        this->destroy();
        MainWindow *w = new MainWindow(false);
        w->show();
    } else {
        ui->incorrectLabel->show();
    }
}
