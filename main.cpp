#include "logindialog.h"
#include <QApplication>
#include "user.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog ld;
    ld.show();

    User::Init();

    return a.exec();
}
