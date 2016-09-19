#include "logindialog.h"
#include "mainwindow.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->incorrectLabel->hide();

    if(User::noRootUser()) {
        User u("", "", true);
        u.save();
        users->append(u);
    }

    users = User::getUsers();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLogin()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    QSharedPointer<User> u(new User(username, password));

    if(users->indexOf(*u) >= 0) {
        this->close();
        MainWindow *w = new MainWindow(u);
        w->show();
    } else {
        ui->incorrectLabel->show();
    }
}
