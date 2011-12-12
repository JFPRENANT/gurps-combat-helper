#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QIODevice>
#include <QXmlStreamReader>

#include "stanza.h"

class XmlParser
{
    public:
        XmlParser();
        static Stanza parse(QIODevice *device);
    private:
//        static void parseStartElement(Stanza * stanza, QXmlStreamReader *reader);
};

#endif // XMLPARSER_H
