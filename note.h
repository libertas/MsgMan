#ifndef NOTE_H
#define NOTE_H

#include "good.h"
#include <QDate>


class Note
{
public:
    static bool Init();
    static bool End();
    static QSharedPointer<Note> CreateByDateId(QDate date, int id);
    static QSharedPointer<QList<Note>> getNotesByDate(QDate date);
    static QSharedPointer<QList<Note>> getNotes();
    static bool Modify(const QList<Note> &notes);

    Note(QDate date, int id, long sellerId, long goodId);

    bool save();

    QDate getDate() const;
    int getId() const;
    long getSellerId() const;
    long getGoodId() const;

private:
    static QSqlDatabase db;
    static bool initialized;

    QDate date;
    int id;
    long sellerId;
    long goodId;
};

#endif // NOTE_H
