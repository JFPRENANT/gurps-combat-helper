#ifndef CHARDELEGATE_H
#define CHARDELEGATE_H

#include <QStyledItemDelegate>

class CharDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    public:
        explicit CharDelegate(QObject *parent = 0);
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CHARDELEGATE_H
