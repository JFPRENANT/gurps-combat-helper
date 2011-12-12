#ifndef XMLTAG_H
#define XMLTAG_H

#include <QString>
#include <QPair>
#include <QList>
#include <QXmlStreamAttributes>

#include "xmlattribute.h"

class XmlTag
{
    public:    
        XmlTag(const QString & name = "", const QString & text = "", const XmlAttributes & attrs = XmlAttributes());
        XmlTag(const QString & name, QVariant value);
        QString name() const;
        XmlAttributes & attrs();
        XmlAttributes const & attrs() const;
        const QString & text() const;
        QString uri() const;
        void setName(const QString & name);
        void setText(const QString & text);
        void addText(const QString & text);
        void setUri(const QString & uri);
        void setAtts(const QXmlStreamAttributes & atts);
        void addAttribute(const QString & name, const QVariant & value);
        void clear();
    private:
        QString m_strName;
        QString m_strText;
        XmlAttributes m_Attributes;        
        QString m_strNamespaceUri;
};

#endif // XMLTAG_H
