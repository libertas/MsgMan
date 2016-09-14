#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "msgman.h"
#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MsgMan *msgman;

public slots:
    void onSearchClicked();
};

#endif // MAINWINDOW_H
