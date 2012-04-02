#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include "character.h"

Character::Character()
{
    _db = Database::inst();
    _isDead = false;
}

void Character::load(int id)
{
    _id = id;
    //load main characteristics
    QSqlQuery query = _db->execSql(QString("SELECT * FROM characters WHERE id = '%1'").arg(id));
    if (query.first()) {
        _name = query.record().value("name").toString();
        _st   = query.record().value("st").toInt();
        _dx   = query.record().value("dx").toInt();
        _iq   = query.record().value("iq").toInt();
        _ht   = query.record().value("ht").toInt();
        _current_hp = _total_hp = query.record().value("hp").toInt();
        _current_fp = _total_fp = query.record().value("fp").toInt();
        _current_posture = 1;
        _current_maneuer = 1;
        _move = query.record().value("bm").toInt();
        _dodge = query.record().value("dodge").toInt();
        _parry = query.record().value("parry").toInt();
        _block = query.record().value("block").toInt();
        _info = query.record().value("notes").toString();
        _bs = query.record().value("bs").toDouble();
    }
}

QString Character::defences() const
{
    return QString("D:%1;P:%2;B:%3").arg(_dodge).arg(_parry).arg(_block);
}

QString Character::effects() const
{
    QString eff = QString();
    if (_current_hp < _total_hp / 3 || _current_fp < _total_fp / 3) {
        eff += QString("Move/2, Dodge/2; ");
    }
    foreach (Effect effect, m_Effects.values()) {
        eff += QString("%1(%2); ").arg(effect.keyword()).arg(effect.modifier());
    }
    QPair<int, QString> manualEffect;
    foreach(manualEffect, _ManualEffects) {
        eff += manualEffect.second + "; ";
    }
    return eff;
}

void Character::changeHp(int delta)
{
    _current_hp += delta;
    if (delta < 0) { //wound
        Effect e("Shock", true, 1, qMax(-4, delta));
        if (m_Effects.contains("Shock")) {
            e.setModifier(qMin(e.modifier(), m_Effects["Shock"].modifier()));
        }
        m_Effects["Shock"] = e;
    }
}

void Character::nextTurn()
{
    qDebug() << "Char next turn";
    foreach(QString eff, m_Effects.keys()) {
        Effect e = m_Effects[eff];
        e.nextTurn();
        m_Effects[eff] = e;
        if (m_Effects[eff].isLasting() && m_Effects.value(eff).turns() < 0) {
            m_Effects.remove(eff);
        }
    }
}

QString Character::info() const
{
    return _info;
}

void Character::save(QDataStream & stream)
{
    stream << _id;
}

void Character::load(QDataStream & stream)
{
    stream >> _id;
    load(_id);
}

void Character::dumpToXml(QXmlStreamWriter * writer)
{
}

QList<QPair<int, QString> > Character::currentManualEffects() const
{
    return _ManualEffects;
}

QSet<int> Character::currentManualEffectsIds() const
{
    QSet<int> res;
    QPair<int, QString> eff;
    foreach(eff, _ManualEffects) {
        res.insert(eff.first);
    }
    return res;
}

void Character::addManualEffect(int id, QString description)
{
    _ManualEffects.append(qMakePair(id, description));
}

void Character::clearManualEffects()
{
    _ManualEffects.clear();
}
