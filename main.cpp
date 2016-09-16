#include "logindialog.h"
#include <QApplication>
#include "user.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    User::Init();

    LoginDialog ld;
    ld.show();

    return a.exec();
}
