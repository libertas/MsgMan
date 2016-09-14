#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtCore>
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    QList<QPair<QString, QString>> rootUsers;
    QList<QPair<QString, QString>> users;

public slots:
    void onLogin();
};

#endif // LOGINDIALOG_H
