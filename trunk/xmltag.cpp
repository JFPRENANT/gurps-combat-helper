#include <QVariant>
#include "xmltag.h"

XmlTag::XmlTag(const QString & name, const QString & text, const XmlAttributes & attrs)
    :m_strName(name), m_strText(text), m_Attributes(attrs)
{
}

XmlTag::XmlTag(const QString & name, QVariant value)
    :m_strName(name), m_strText(value.toString())
{
}

QString XmlTag::name() const
{
    return m_strName;
}

XmlAttributes & XmlTag::attrs()
{
    return m_Attributes;
}

XmlAttributes const & XmlTag::attrs() const
{
    return m_Attributes;
}

const QString & XmlTag::text() const
{
    return m_strText;
}

QString XmlTag::uri() const
{
    return m_strNamespaceUri;
}

void XmlTag::setName(const QString & name)
{
    m_strName = name;
}

void XmlTag::setText(const QString & text)
{
    m_strText = text;    
}

void XmlTag::addText(const QString & text)
{
    m_strText += text;
}

void XmlTag::setUri(const QString & uri)
{
    m_strNamespaceUri = uri;
}

void XmlTag::setAtts(const QXmlStreamAttributes & atts)
{
    m_Attributes.clear();
    foreach(QXmlStreamAttribute att, atts) {
        m_Attributes.append(XmlAttribute(att.name().toString(), att.value().toString()));
    }
}

void XmlTag::clear()
{
    m_Attributes.clear();
    m_strName.clear();
    m_strNamespaceUri.clear();
    m_strText.clear();
}

void XmlTag::addAttribute(const QString & name, const QVariant & value)
{
    m_Attributes.append(XmlAttribute(name, value.toString()));
}
