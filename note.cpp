#include "note.h"
#include <assert.h>
#include <QSqlQuery>

QSqlDatabase Note::db;
bool Note::initialized;


bool Note::Init()
{
    assert(!Note::initialized);
    Note::db = QSqlDatabase::addDatabase("QSQLITE", "connNote");
    Note::db.setDatabaseName("notes.db");
    Note::initialized = true;

    Note::db.open();

    QSqlQuery query("", Note::db);
    query.exec("CREATE TABLE IF NOT EXISTS notes (time, id, sellerId, goodId)");

    Note::db.commit();
    Note::db.close();

    return true;
}

bool Note::End()
{
    assert(Note::initialized);

    QSqlDatabase::removeDatabase(Note::db.connectionName());

    Note::initialized = false;

    return true;
}

QSharedPointer<Note> Note::CreateByTimeId(QDateTime time, int id)
{
    assert(Note::initialized);
    long sellerId;
    long goodId;

    Note::db.open();
    QSqlQuery query("", Note::db);

    query.prepare("SELECT * FROM notes WHERE (id=? AND time = ?)");
    query.addBindValue(QString::number(id, 10));
    query.addBindValue(time.toString());
    if(query.exec() && query.next()) {
        sellerId = query.value(2).toInt();
        goodId = query.value(3).toInt();
    } else {
        sellerId = 0;
        goodId = 0;
    }

    Note::db.close();

    QSharedPointer<Note> s(new Note(time, id, sellerId, goodId));
    return s;
}

QSharedPointer<QList<Note> > Note::getNotes()
{
    assert(Note::initialized);

    QSharedPointer<QList<Note>> notes(new QList<Note>);

    Note::db.open();

    QSqlQuery query("", Note::db);

    query.prepare("SELECT * FROM notes");
    query.exec();
    while(query.next()) {
        Note note = Note(QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm:ss"),
                         query.value(1).toInt(),
                         query.value(2).toInt(),
                         query.value(3).toInt());
        notes->append(note);
    }

    Note::db.close();

    return notes;
}

bool Note::Modify(const QList<Note> &notes)
{
    assert(Note::initialized);
    Note::db.open();
    QSqlQuery query("", Note::db);

    query.prepare("DELETE FROM notes");
    query.exec();

    for(QList<Note>::const_iterator iter = notes.begin(); iter != notes.end(); iter++) {
        query.prepare("REPLACE INTO notes VALUES (?, ?, ?, ?)");
        query.addBindValue(iter->getTime().toString());
        query.addBindValue(QString::number(iter->getId(), 10));
        query.addBindValue(QString::number(iter->getSellerId()));
        query.addBindValue(QString::number(iter->getGoodId()));
        assert(query.exec());
    }

    Note::db.commit();
    Note::db.close();

    return true;
}

Note::Note(QDateTime time, int id, long noteId, long goodId)
{
    assert(Note::initialized);

    this->time = time;
    this->id = id;
    this->sellerId = noteId;
    this->goodId = goodId;
}

bool Note::save()
{
    assert(Note::initialized);

    return true;
}

QDateTime Note::getTime() const
{
    return this->time;
}

int Note::getId() const
{
    return this->id;
}

long Note::getSellerId() const
{
    return this->sellerId;
}

long Note::getGoodId() const
{
    return this->goodId;
}
