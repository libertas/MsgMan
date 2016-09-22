#include "errordialog.h"
#include "good.h"
#include "note.h"
#include "seller.h"
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

        this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

NoteManage::~NoteManage()
{
    delete ui;
}

void NoteManage::onApplyClicked()
{
    if(this->user->getIsRoot()) {
        QList<Note> notes;

        QString dateStr = ui->dateEdit->text();
        QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
        if(date.isValid()) {
            for(long row = 0; row != ui->tableWidget->rowCount(); row++) {

                    int id = ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toInt();
                    long sellerId = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toInt();
                    long goodId = ui->tableWidget->item(row, 3)->data(Qt::DisplayRole).toInt();

                    Note note(date, id, sellerId, goodId);
                    notes.append(note);
            }

            Note::Modify(notes);
        } else {
            ErrorDialog *ed = new ErrorDialog(this, "Invalid Date");
            ed->show();
        }
    }
}

void NoteManage::onResetClicked()
{
    NoteManage *nm = new NoteManage(this->user);
    this->close();
    nm->show();
}

void NoteManage::onAddClicked()
{
    if(this->user->getIsRoot()) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString("0")));

        QTableWidgetItem *sellerNameItem = new QTableWidgetItem(QString("Seller"));
        sellerNameItem->setFlags(sellerNameItem->flags() & (~Qt::ItemIsEditable));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, sellerNameItem);

        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString("0")));

        QTableWidgetItem *goodNameItem = new QTableWidgetItem(QString("Good"));
        goodNameItem->setFlags(goodNameItem->flags() & (~Qt::ItemIsEditable));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, goodNameItem);

        QTableWidgetItem *goodPriceItem = new QTableWidgetItem(QString("0"));
        goodPriceItem->setFlags(goodPriceItem->flags() & (~Qt::ItemIsEditable));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, goodPriceItem);
    }
}

void NoteManage::onDeleteClicked()
{
    if(this->user->getIsRoot()) {
        QList<QTableWidgetSelectionRange> ranges = ui->tableWidget->selectedRanges();
        for(long i = ranges.count() - 1; i >= 0; i--) {
            long topRow = ranges.at(i).topRow();
            long bottomRow = ranges.at(i).bottomRow();
            for(long j = bottomRow; j >= topRow; j--){
                ui->tableWidget->removeRow(j);
            }
        }
    }
}

void NoteManage::onOpenClicked()
{
    QString dateStr = ui->dateEdit->text();
    QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
    if(date.isValid()) {
        QSharedPointer<QList<Note>> notes = Note::getNotesByDate(date);

        for(QList<Note>::Iterator iter = notes->begin(); iter != notes->end(); iter++) {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(iter->getId(), 10)));

            long sellerId = iter->getSellerId();

            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(sellerId, 10)));
            QSharedPointer<Seller> seller = Seller::CreateById(sellerId);

            QTableWidgetItem *sellerNameItem = new QTableWidgetItem(seller->getName());
            sellerNameItem->setFlags(sellerNameItem->flags() & (~Qt::ItemIsEditable));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, sellerNameItem);

            long goodId = iter->getGoodId();
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString::number(goodId)));

            QSharedPointer<Good> good = Good::CreateById(goodId);

            QTableWidgetItem *goodNameItem = new QTableWidgetItem(good->getName());
            goodNameItem->setFlags(goodNameItem->flags() & (~Qt::ItemIsEditable));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, goodNameItem);

            QTableWidgetItem *goodPriceItem = new QTableWidgetItem(QString::number(good->getPrice(), 10));
            goodPriceItem->setFlags(goodPriceItem->flags() & (~Qt::ItemIsEditable));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, goodPriceItem);
        }
    } else {
        ErrorDialog *ed = new ErrorDialog(this, "Invalid Date");
        ed->show();
    }
}

void NoteManage::onItemChanged(QTableWidgetItem *item)
{
    QSharedPointer<Seller> seller;
    QSharedPointer<Good> good;
    QTableWidgetItem *sellerNameItem;
    QTableWidgetItem *goodNameItem;
    QTableWidgetItem *goodPriceItem;
    long sellerId;
    long goodId;


    int row = item->row();
    int col = item->column();

    if(item->isSelected()) {
        switch(col) {
        case 1:
            sellerNameItem = ui->tableWidget->item(row, col + 1);
            sellerId = item->data(Qt::DisplayRole).toInt();
            seller = Seller::CreateById(sellerId);
            sellerNameItem->setText(seller->getName());
            break;
        case 3:
            goodNameItem = ui->tableWidget->item(row, col + 1);
            goodPriceItem = ui->tableWidget->item(row, col + 2);
            goodId = item->data(Qt::DisplayRole).toInt();
            good = Good::CreateById(goodId);
            goodNameItem->setText(good->getName());
            goodPriceItem->setText(QString::number(good->getPrice(), 10));
            break;
        default:
            break;
        }
    }
}
