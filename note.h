#ifndef NOTE_H
#define NOTE_H

#include "good.h"
#include <QDateTime>


class Note
{
public:
    static bool Init();
    static bool End();
    static QSharedPointer<Note> CreateByTimeId(QDateTime time, int id);
    static QSharedPointer<QList<Note>> getNotes();
    static bool Modify(const QList<Note> &notes);

    Note(QDateTime time, int id, long goodId);

    bool save();

    QDateTime getTime() const;
    int getId() const;
    long getGoodId() const;

private:
    static QSqlDatabase db;
    static bool initialized;

    QDateTime time;
    int id;
    long goodId;
};

#endif // NOTE_H
