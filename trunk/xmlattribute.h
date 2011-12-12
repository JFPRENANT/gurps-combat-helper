#ifndef XMLATTRIBUTE_H
#define XMLATTRIBUTE_H

#include <QList>
#include <QString>

class XmlAttribute        
{
    public:
        XmlAttribute(const QString & name = "", const QString & value = "") : m_strName(name), m_strValue(value){}
        QString const & name() const { return m_strName; }
        QString const & value() const { return m_strValue; }
        void setName(const QString & name) { m_strName = name; }
        void setValue(const QString & value) { m_strValue = value; }
        bool operator==(const QString &name) const  { return m_strName == name; }
    private:
        QString m_strName;
        QString m_strValue;
};

class XmlAttributes : public QList<XmlAttribute>
{
    public:
        bool has(const QString & name) const;
        XmlAttribute & attr(const QString & name);
        XmlAttribute const & attr(const QString & name) const;
};

#endif // XMLATTRIBUTE_H
