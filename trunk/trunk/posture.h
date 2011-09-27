#ifndef POSTURE_H
#define POSTURE_H

#include <QString>
#include <QSqlRecord>

class Posture
{
    public:
        Posture(int id =0, const QString & name = QString(), const QString & tooltip = QString());
        Posture(const QSqlRecord & record);
        int id() const { return _id; }
        QString name() const { return _name; }
        QString toolitp() const { return _tooltip; }
    private:
        int _id;
        QString _name;
        QString _tooltip;
};

#endif // POSTURE_H
