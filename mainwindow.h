#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "user.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(User *u);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    User *user;

public slots:
    void onUserClicked();
    void onBranchClicked();
    void onBranchesClicked();
    void onSellClicked();
    void onSearchClicked();
    void onSalaryClicked();
};

#endif // MAINWINDOW_H
