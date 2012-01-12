#include "selectmodel.h"

SelectModel::SelectModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int SelectModel::rowCount(const QModelIndex &parent) const
{
    return rowCount();
}

int SelectModel::rowCount() const
{
    return m_Data.size();
}

QVariant SelectModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole : return m_Data.at(index.row()).second;
        case IdRole: return m_Data.at(index.row()).first;
    }
    return QVariant();
}

void SelectModel::add(const QPair<int, QString> piece)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Data.append(piece);
    endInsertRows();
}

void SelectModel::clear()
{
    if (!m_Data.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        m_Data.clear();
        endRemoveRows();
    }
}

QPair<int, QString> SelectModel::element(int row)
{
    if (row > -1 && row < m_Data.size()) {
        return m_Data[row];
    } else {
        return QPair<int, QString>();
    }
}

bool SelectModel::removeRows(int row, int count, const QModelIndex &parent)
{
    emit beginRemoveRows(parent, row, count);
    for (int i = 0; i < count; ++i) {
        m_Data.removeAt(row);
    }
    emit endRemoveRows();
}
