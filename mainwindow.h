#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool isRoot);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void onUserClicked();
    void onBranchClicked();
    void onSellClicked();
    void onSearchClicked();
    void onSalaryClicked();
};

#endif // MAINWINDOW_H
