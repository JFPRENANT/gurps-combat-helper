#include <QPainter>
#include "chardelegate.h"
#include "charactermodel.h"

CharDelegate::CharDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void CharDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data(CharacterModel::CurrentRole).toBool()) {
        painter->fillRect(option.rect, QColor(230, 230, 230));
    } else {
        painter->fillRect(option.rect, Qt::white);
    }
    painter->drawText(option.rect, index.data(Qt::DisplayRole).toString(), QTextOption(Qt::AlignCenter));
}
