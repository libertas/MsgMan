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
    query.exec("CREATE TABLE IF NOT EXISTS notes (time, id, goodId)");

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
                         query.value(2).toInt());
        notes->append(note);
    }

    Note::db.close();

    return notes;
}

Note::Note(QDateTime time, int id, long goodId)
{
    assert(Note::initialized);

    this->time = time;
    this->id = id;
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

long Note::getGoodId() const
{
    return this->goodId;
}
