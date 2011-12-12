#include <QXmlStreamWriter>
#include "stanza.h"

Stanza::Stanza()
{
}

Stanza::Stanza(const XmlTag & tag)
    :m_MainTag(tag)
{
}

Stanza::~Stanza()
{
}

XmlTag const & Stanza::tag() const
{
    return m_MainTag;
}

XmlTag & Stanza::tag()
{
    return m_MainTag;
}

StanzaList const & Stanza::childs() const
{
    return m_Childs;
}

StanzaList & Stanza::childs()
{
    return m_Childs;
}

Stanza & Stanza::child(int nIndex)
{
    return m_Childs[nIndex];
}

Stanza const & Stanza::child(int nIndex) const
{
    return m_Childs[nIndex];
}

void Stanza::setTag(const XmlTag & tag)
{
    m_MainTag = tag;
}

Stanza * Stanza::addChild(const Stanza & child)
{
    m_Childs.append(child);
    return &m_Childs[m_Childs.size() - 1];
}

void Stanza::toXml(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(m_MainTag.name());
    if (!m_MainTag.uri().isEmpty()) {
        writer->writeDefaultNamespace(m_MainTag.uri());
    }
    foreach (XmlAttribute att, m_MainTag.attrs()) {
        writer->writeAttribute(att.name(), att.value());
    }
    if (!m_MainTag.text().isEmpty()) {
        writer->writeCharacters(m_MainTag.text());
    }
    foreach (Stanza st, m_Childs) {
        st.toXml(writer);
    }
    writer->writeEndElement();
}

void Stanza::clear()
{
    m_MainTag.clear();
    m_Childs.clear();
}

Stanza const & Stanza::child(const QString & tagName) const
{
    for (int i = 0; i < m_Childs.count(); ++i) {
        if (m_Childs[i].tag().name() == tagName) {
            return m_Childs[i];
        }
    }
    return *this;
}

Stanza & Stanza::child(const QString & tagName)
{
    for (int i = 0; i < m_Childs.count(); ++i) {
        if (m_Childs[i].tag().name() == tagName) {
            return m_Childs[i];
        }
    }
    return *this;
}
