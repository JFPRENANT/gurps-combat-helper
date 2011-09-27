#include <QVariant>
#include "maneuer.h"

Maneuer::Maneuer(int id, const QString & name, const QString & tooltip)
    :_name(name), _tooltip(tooltip)
{}

Maneuer::Maneuer(const QSqlRecord & record)
{
    _id = record.value("id").toInt();
    _name = record.value("name").toString();
    _tooltip = record.value("tooltip").toString();
}
