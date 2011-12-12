
#include "xmlattribute.h"

bool XmlAttributes::has(const QString & name) const
{
    return qFind(*this, name) != constEnd();
}

XmlAttribute & XmlAttributes::attr(const QString & name)
{
    static XmlAttribute defaultAttr;
    for (int i = 0; i < size(); ++i) {
        if (at(i).name() == name) {
            return operator[](i);
        }
    }
    return defaultAttr = XmlAttribute();
}

XmlAttribute const & XmlAttributes::attr(const QString & name) const
{
    static XmlAttribute defaultAttr;
    for (int i = 0; i < size(); ++i) {
        if (at(i).name() == name) {
            return operator[](i);
        }
    }
    return defaultAttr = XmlAttribute();
}
