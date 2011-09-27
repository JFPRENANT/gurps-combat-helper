#include <QVariant>
#include "posture.h"

Posture::Posture(int id, const QString & name, const QString & tooltip)
    :_id(id), _name(name), _tooltip(tooltip)
{}

Posture::Posture(const QSqlRecord & record)
{
    _id = record.value("id").toInt();
    _name = record.value("name").toString();
    _tooltip = record.value("tooltip").toString();
}
