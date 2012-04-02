#include <QDebug>
#include <QPainter>
#include "chardelegate.h"
#include "charactermodel.h"

CharDelegate::CharDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void CharDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.data(CharacterModel::CurrentRole).toInt()) {
        case CharacterModel::CHAR_IS_CURRENT:
            painter->fillRect(option.rect, QColor(230, 230, 230));
            break;
        case CharacterModel::CHAR_NOT_CURRENT:
            painter->fillRect(option.rect, Qt::white);
            break;
        case CharacterModel::CHAR_IS_DEAD:
            painter->fillRect(option.rect, QColor(230, 150, 150));
            break;
    }
    painter->drawText(option.rect, index.data(Qt::DisplayRole).toString(), QTextOption(Qt::AlignCenter));
}
