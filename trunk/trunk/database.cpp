#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include "database.h"

Database * Database::inst()
{
    static Database * inst = new Database();
    return inst;
}

Database::Database()
{
    m_Connection = QSqlDatabase::addDatabase("QSQLITE");
    m_Connection.setDatabaseName("database.db");
    if (!m_Connection.open()) {
        qDebug() << "Can't open database";
    }    
}

Database::~Database()
{
    m_Connection.close();
}

void Database::createStructure()
{
    QStringList queries;
    queries << "CREATE TABLE IF NOT EXISTS categories (id INTEGER PRIMARY KEY, name TEXT)"
    << "CREATE TABLE IF NOT EXISTS characters (block NUMERIC, bm NUMERIC, bs NUMERIC, category_id NUMERIC, dodge NUMERIC, dr_arms NUMERIC, dr_face NUMERIC, dr_foots NUMERIC, dr_hands NUMERIC, dr_legs NUMERIC, dr_neck NUMERIC, dr_skull NUMERIC, dr_torso NUMERIC, dx NUMERIC, fp NUMERIC, hp NUMERIC, ht NUMERIC, id INTEGER PRIMARY KEY, iq NUMERIC, name TEXT, notes TEXT, parry NUMERIC, per NUMERIC, st NUMERIC, will NUMERIC)"
    << "CREATE TABLE IF NOT EXISTS manevrous (id INTEGER PRIMARY KEY, name TEXT, tooltip TEXT)"
    << "CREATE TABLE IF NOT EXISTS postures (id INTEGER PRIMARY KEY, name TEXT, tooltip TEXT)";
    foreach (QString query, queries) {
        execSql(query);
    }

}

QSqlQuery Database::execSql(const QString & sql)
{
    QSqlQuery query(sql, m_Connection);
    if (query.lastError().isValid()) {
        qDebug() << "Database error: " << query.lastError().text();
        qDebug() << sql;
    }
    return query;
}

QString Database::escape(const QString & str)
{
    QString res;
    for (QString::const_iterator it = str.begin(); it != str.end(); ++it) {
        switch (it->toAscii()) {
            case '\'':
                res.append("''");
                break;
            default:
                res.append(*it);
        }
    }
    return res;
}

IdNameList<IdName> Database::getCategories()
{
    QSqlQuery query = execSql("SELECT id, name FROM categories WHERE 1=1");
    IdNameList<IdName> res;
    while (query.next()) {
        res << IdName(query.record().value("name").toString(), query.record().value("id").toInt());
    }
    return res;
}

IdNameList<IdName> Database::getCharacters(int nCategoryId)
{
    QSqlQuery query = execSql(QString("SELECT id, name FROM characters WHERE category_id='%1'").arg(nCategoryId));
    IdNameList<IdName> res;
    while (query.next()) {
        res << IdName(query.record().value("name").toString(), query.record().value("id").toInt());
    }
    return res;
}


int Database::createCategory(const QString & name)
{
    return execSql(QString("INSERT INTO categories (name) VALUES ('%1')").arg(name)).lastInsertId().toInt();
}

void Database::deleteCategory(int nId)
{
    execSql(QString("DELETE FROM categories WHERE id = '%1'").arg(nId));
}

QVariantMap Database::getCharacter(int nId)
{
    QSqlQuery query = execSql(QString("SELECT * FROM characters WHERE id = '%1'").arg(nId));
    QVariantMap res;
    if (query.first()) {
        for (int i = 0; i < query.record().count(); ++i) {
            res[query.record().fieldName(i)] = query.record().value(i);
        }
    }
    return res;
}

int Database::saveCharacter(const QVariantMap & character)
{
    QString sql;    
    bool bSet;    
    QVariantMap data(character);
    int nCharId = data[ID].toInt();
    if (nCharId == 0) { // new character
        sql = "INSERT INTO characters (`%1`) VALUES ('%2')";
        bSet = false;
    } else {
        sql = QString("UPDATE characters SET %2 WHERE id = '%1'").arg(nCharId);
        bSet = true;
    }
    data.remove(ID);
    QStringList names, values;
    for (QVariantMap::iterator it = data.begin(); it != data.end(); ++it) {
        if (bSet) {
            names << QString("`%1` = '%2'").arg(it.key(), escape(it.value().toString()));
        } else {
            names << it.key();
            values << escape(it.value().toString());
        }
    }
    if (bSet) {
        sql = sql.arg(names.join(","));
    } else {
        sql = sql.arg(names.join("`,`"), values.join("','"));
    }
    QSqlQuery q = execSql(sql);
    if (!nCharId) nCharId = q.lastInsertId().toInt();
    return nCharId;
}

void Database::deleteCharacter(int nId)
{
    execSql(QString("DELETE FROM characters WHERE id = '%1'").arg(nId));
}


TrackingCharacter Database::getCharForTracking(int nId)
{
    QSqlQuery query = execSql(QString("SELECT * FROM characters WHERE id = '%1'").arg(nId));
    TrackingCharacter character;
    if (query.first()) {
        character.setName(query.record().value(NAME).toString());
        character.setSt(query.record().value(ST).toInt());
        character.setDx(query.record().value(DX).toInt());
        character.setIq(query.record().value(IQ).toInt());
        character.setHt(query.record().value(HT).toInt());
    }
    return character;
}

QMap<int, Maneuer> Database::maneuers()
{
    QSqlQuery query = execSql("SELECT * FROM manevrous");
    QMap<int, Maneuer> res;
    while(query.next()) {
        res.insert(query.record().value("id").toInt(), Maneuer(query.record()));
    }
    return res;
}

QMap<int, Posture> Database::postures()
{
    QSqlQuery query = execSql("SELECT * FROM postures");
    QMap<int, Posture> res;
    while(query.next()) {
        res.insert(query.record().value("id").toInt(), Posture(query.record()));
    }
    return res;
}

void Database::setupSelectModel(SelectModel *model, const QString & table, const QString & IdField, const QString &  NameField)
{
    model->clear();
    QSqlQuery query = execSql(QString("SELECT `%1`, `%2` FROM `%3`").arg(IdField, NameField, table));
    while(query.next()) {
        model->add(qMakePair(query.record().value(IdField).toInt(), query.record().value(NameField).toString()));
    }
}
