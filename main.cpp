#include "logindialog.h"
#include <QApplication>
#include "user.h"
#include "branch.h"
#include "good.h"
#include "note.h"
#include "seller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    User::Init();
    Branch::Init();
    Seller::Init();
    Good::Init();
    Note::Init();

    LoginDialog ld;
    ld.show();

    int re = a.exec();

    User::End();
    Branch::End();
    Seller::End();
    Good::End();
    Note::End();

    return re;
}
