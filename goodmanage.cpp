#include "goodmanage.h"
#include "ui_goodmanage.h"


GoodManage::GoodManage(QSharedPointer<User> u) :
    QWidget(0),
    ui(new Ui::GoodManage)
{
    ui->setupUi(this);
    this->user = u;
}

GoodManage::~GoodManage()
{
    delete ui;
}

void GoodManage::onApplyClicked()
{

}

void GoodManage::onResetClicked()
{

}

void GoodManage::onAddClicked()
{

}

void GoodManage::onDeleteClicked()
{

}
