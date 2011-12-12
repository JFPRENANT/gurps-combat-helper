#ifndef STANZA_H
#define STANZA_H

#include <QList>
#include <QXmlStreamWriter>
#include <QMetaType>

#include "xmltag.h"

class Stanza;

typedef QList<Stanza> StanzaList;

class Stanza
{
    public:
        Stanza();
        Stanza(const XmlTag & tag);
        virtual ~Stanza();
        XmlTag const & tag() const;
        XmlTag & tag();
        StanzaList const & childs() const;
        StanzaList & childs();
        Stanza const & child(int index) const;
        Stanza & child(int index);
        Stanza const & child(const QString & tagName) const;
        Stanza & child(const QString & tagName);
        void setTag(const XmlTag & tag);
        Stanza * addChild(const Stanza & child);
        void toXml(QXmlStreamWriter *writer) const;
        void clear();
    protected:
        XmlTag m_MainTag;        
        StanzaList m_Childs;
};



Q_DECLARE_METATYPE(Stanza);

#endif // STANZA_H
