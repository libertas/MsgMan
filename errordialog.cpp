#include "errordialog.h"
#include "ui_errordialog.h"


ErrorDialog::ErrorDialog(QWidget *parent, QString message) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
    ui->msgLabel->setText(message);
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}
