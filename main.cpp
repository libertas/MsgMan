#include "mainwindow.h"
#include "msgman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MsgMan *msgman = new MsgMan("abc");

    return a.exec();
}
