#ifndef MANEUER_H
#define MANEUER_H

#include <QString>
#include <QSqlRecord>

class Maneuer
{
    public:
        Maneuer(int id = 1, const QString & name = QString(), const QString & tooltip = QString());
        Maneuer(const QSqlRecord & record);
        int id() const { return _id; }
        QString name() const { return _name; }
        QString tooltip() const { return _tooltip; }
    private:
        int _id;
        QString _name;
        QString _tooltip;
};

#endif // MANEUER_H
