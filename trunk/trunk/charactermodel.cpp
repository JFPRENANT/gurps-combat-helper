#include <QDebug>
#include <QFile>
#include "charactermodel.h"
#include "database.h"
#include "manualeffectsselector.h"

CharacterModel::CharacterModel(QObject *parent) :
    QAbstractTableModel(parent), _current_char(-1)
{
    m_Maneuers = Database::inst()->maneuers();
    m_Postures = Database::inst()->postures();
}

int CharacterModel::columnCount(const QModelIndex &) const
{
    return columnCount();
}

int CharacterModel::rowCount(const QModelIndex &) const
{
    return rowCount();
}

int CharacterModel::columnCount() const
{
    return COLUMN_COUNT;
}

int CharacterModel::rowCount() const
{
    return m_Characters.size();
}

void CharacterModel::addCharacter(Character *ch)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Characters.append(ch);
    m_Encounter.append(ch);
    endInsertRows();
}

void CharacterModel::addCharacter(int nId)
{
    Character *ch = new Character;
    ch->load(nId);
    addCharacter(ch);
}

void CharacterModel::changeHp(int row, int delta)
{
    if (m_Characters.isEmpty()) return;
    m_Characters.at(row)->changeHp(delta);
    emit dataChanged(index(row, HP), index(row, HP));
}

void CharacterModel::changeFp(int row, int delta)
{
    if (m_Characters.isEmpty()) return;
    m_Characters.at(row)->changeFp(delta);
    emit dataChanged(index(row, FP), index(row, FP));
}

void CharacterModel::selectPosture(int row, int id)
{
    if(m_Characters.isEmpty()) return;
    m_Characters.at(row)->setPosture(id);
    emit dataChanged(index(row, POSTURE), index(row, POSTURE));
}

void CharacterModel::selectManeuer(int row, int id)
{
    if (m_Characters.isEmpty()) return;
    m_Characters.at(row)->setManuer(id);
    emit dataChanged(index(row, MANEUER), index(row, MANEUER));
}

QVariant CharacterModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
        case Qt::DisplayRole: return displayData(index);
        case Qt::ToolTipRole: return toolTipData(index);
        case CurrentRole: return index.row() == _current_char;
    }
    return QVariant();
}

bool CharacterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(index.column()) {
        case HP:
            m_Characters.at(index.row())->changeHp(value.toInt());
            emit dataChanged(index, index);
            return true;
        case FP:
            m_Characters.at(index.row())->changeFp(value.toInt());
            emit dataChanged(index, index);
            return true;
    }
    return false;
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex &index) const
{
    switch(index.column()) {
        case HP:
        case FP:
            return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    return Qt::ItemIsEnabled;
}

QVariant CharacterModel::displayData(const QModelIndex & index) const
{
    switch ((Columns)index.column()) {
        case NAME: return m_Characters[index.row()]->name();
        case ST: return m_Characters[index.row()]->st();
        case DX: return m_Characters[index.row()]->dx();
        case IQ: return m_Characters[index.row()]->iq();
        case HT: return m_Characters[index.row()]->ht();
        case HP: return QString("%1/%2").arg(m_Characters[index.row()]->current_hp()).arg(m_Characters[index.row()]->hp());
        case FP: return QString("%1/%2").arg(m_Characters[index.row()]->current_fp()).arg(m_Characters[index.row()]->fp());
        case MANEUER: return m_Maneuers.value(m_Characters[index.row()]->maneuer()).name();
        case POSTURE: return m_Postures.value(m_Characters[index.row()]->posture()).name();
        case MOVE: return m_Characters[index.row()]->move();
        case DEFENCES: return m_Characters[index.row()]->defences();
        case EFFECTS: return m_Characters[index.row()]->effects();
    }
    return QVariant();
}

QVariant CharacterModel::toolTipData(const QModelIndex & index) const
{
    switch((Columns)index.column()) {
        case MANEUER: return m_Maneuers.value(m_Characters[index.row()]->maneuer()).tooltip();
        case POSTURE: return m_Postures.value(m_Characters[index.row()]->posture()).toolitp();
    }
    return QVariant();
}

QVariant CharacterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        switch((Columns)(section)) {
            case NAME: return "Name";
            case ST: return "ST";
            case DX: return "DX";
            case IQ: return "IQ";
            case HT: return "HT";
            case HP: return "HP";
            case FP: return "FP";
            case POSTURE: return "Posture";
            case MANEUER: return "Maneuer";
            case EFFECTS: return "Character effects";
            case MOVE: return "Move";
            case DEFENCES: return "Defences";
        }
    return QVariant();
}

void CharacterModel::startBattle()
{
    if (m_Characters.isEmpty()) {
        return;
    }
    qSort(m_Characters.begin(), m_Characters.end(), charLessThan);
    _current_char = 0;
    _turn = 1;
    emit dataChanged(index(_current_char, 0), index(_current_char, COLUMN_COUNT - 1));
    emit turnChanged(_turn);
    emit infoChanged(m_Characters[_current_char]->info());
}

void CharacterModel::nextChar()
{
    if(m_Characters.isEmpty()) return;
    ++_current_char;
    if (_current_char >= m_Characters.size()) {
        ++_turn;
        emit turnChanged(_turn);
        _current_char = 0;
    }
    m_Characters[_current_char]->nextTurn();
    emit dataChanged(index(_current_char, 0), index(_current_char, COLUMN_COUNT - 1));
    emit infoChanged(m_Characters[_current_char]->info());
}

void CharacterModel::onDictionariesUpdate()
{
    m_Maneuers = Database::inst()->maneuers();
    m_Postures = Database::inst()->postures();
}

bool CharacterModel::charLessThan(Character *c1, Character *c2)
{
    return c1->bs() > c2->bs();
}

QList<Character *> CharacterModel::chars() const
{
    return m_Characters;
}

void CharacterModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    foreach (Character *ch, m_Characters) {
        delete ch;
    }
    m_Characters.clear();
    endRemoveRows();
}

void CharacterModel::saveToFile(const QString & filename)
{
    QFile f(filename);
    if (f.open(QIODevice::WriteOnly)) {
        QDataStream stream(&f);
        stream << (quint32)m_Characters.size();
        foreach(Character *ch, m_Characters) {
            ch->save(stream);
        }
        f.close();
    }

}

void CharacterModel::loadParty(const QString & filename)
{
    QFile f(filename);
    if (f.open(QIODevice::ReadOnly)) {
        m_Characters.clear();
        if (!m_Party.isEmpty()) {
            foreach (Character * ch, m_Party) {
                delete ch;
            }
            m_Party.clear();
        }
        QDataStream stream(&f);
        quint32 size;
        stream >> size;
        for (int i = 0; i < size; ++i) {
            Character *ch = new Character;
            ch->load(stream);
            m_Party.append(ch);
        }
        f.close();
        reArrangeRows();
    }
}

void CharacterModel::loadEncounter(const QString & filename)
{
    QFile f(filename);
    if (f.open(QIODevice::ReadOnly)) {
        QDataStream stream(&f);
        clearEncounter();
        quint32 size;
        stream >> size;
        for(int i = 0; i < size; ++i) {
            Character *ch = new Character;
            ch->load(stream);
            m_Encounter.append(ch);
        }
        f.close();
        reArrangeRows();
    }
}

void CharacterModel::clearEncounter()
{
    foreach(Character *ch, m_Encounter) {
        delete ch;
    }
    m_Encounter.clear();
    reArrangeRows();
}

void CharacterModel::reArrangeRows()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_Characters.clear();
    endRemoveRows();
    m_Characters = m_Party + m_Encounter;
    if (m_Characters.size()) {
        beginInsertRows(QModelIndex(), 0, m_Characters.size() - 1);
        endInsertRows();
    }
}

void CharacterModel::changeManualEffects(int row)
{
    if (row < 0 || row >= m_Characters.size()) return;
    ManualEffectsSelector selector;
    selector.init(m_Characters[row]);
    selector.exec();
    selector.setupCharacter(m_Characters[row]);
    emit dataChanged(index(row, EFFECTS), index(row, EFFECTS));
}
