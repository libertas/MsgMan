#ifndef NOTEMANAGE_H
#define NOTEMANAGE_H

#include "user.h"
#include <QTableWidget>
#include <QWidget>

namespace Ui {
class NoteManage;
}

class NoteManage : public QWidget
{
    Q_OBJECT

public:
    explicit NoteManage(QSharedPointer<User> u);
    ~NoteManage();

private:
    Ui::NoteManage *ui;
    QSharedPointer<User> user;

public slots:
    void onApplyClicked();
    void onResetClicked();
    void onAddClicked();
    void onDeleteClicked();
    void onOpenClicked();
    void onItemChanged(QTableWidgetItem *item);
};

#endif // NOTEMANAGE_H
