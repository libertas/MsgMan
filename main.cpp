#include "logindialog.h"
#include <QApplication>
#include "user.h"
#include "branch.h"
#include "seller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    User::Init();
    Branch::Init();
    Seller::Init();

    LoginDialog ld;
    ld.show();

    int re = a.exec();

    User::End();
    Branch::End();
    Seller::End();

    return re;
}
