#ifndef SELECTMODEL_H
#define SELECTMODEL_H

#include <QAbstractListModel>

class SelectModel : public QAbstractListModel
{
    Q_OBJECT
    public:

        static const int IdRole = Qt::UserRole;

        explicit SelectModel(QObject *parent = 0);
        int rowCount(const QModelIndex &parent) const;
        int rowCount() const;
        QVariant data(const QModelIndex &index, int role) const;
        void add(const QPair<int, QString> piece);
        void clear();
    private:
        QList<QPair<int, QString> > m_Data;
};

#endif // SELECTMODEL_H
