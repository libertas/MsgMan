#include "notemanage.h"
#include "ui_notemanage.h"

NoteManage::NoteManage(QSharedPointer<User> u) :
    QWidget(0),
    ui(new Ui::NoteManage)
{
    ui->setupUi(this);
    this->user = u;

    if(!this->user->getIsRoot()) {
        this->ui->addButton->hide();
        this->ui->deleteButton->hide();
        this->ui->applyButton->hide();
    }
}

NoteManage::~NoteManage()
{
    delete ui;
}

void NoteManage::onApplyClicked()
{

}

void NoteManage::onResetClicked()
{

}

void NoteManage::onAddClicked()
{

}

void NoteManage::onDeleteClicked()
{

}
