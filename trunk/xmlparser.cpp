#include <QDebug>
#include <QStack>
#include "xmlparser.h"

XmlParser::XmlParser()
{
}

Stanza XmlParser::parse(QIODevice *device)
{
    Stanza res;
//    Stanza *currentStanza = & res;
    QStack<Stanza *> parseStack;
    QXmlStreamReader reader(device);
    while (!reader.atEnd()) {
        reader.readNext();
        switch (reader.tokenType()) {
//        case QXmlStreamReader::StartDocument:
//            break;
        case QXmlStreamReader::StartElement:
            if (parseStack.isEmpty()) {
                parseStack.push(&res);
            } else {
                parseStack.push(parseStack.top()->addChild(Stanza()));
            }
            parseStack.top()->tag().setName(reader.name().toString());
            parseStack.top()->tag().setAtts(reader.attributes());
            break;
        case QXmlStreamReader::Characters:
            parseStack.top()->tag().setText(reader.text().toString());
            break;
        case QXmlStreamReader::EndElement:
            parseStack.pop();
            break;
        case QXmlStreamReader::Invalid:
            qDebug() << "Invalid element";
            break;
        default:
            qDebug() << "Non handled token " << reader.tokenType();
            break;
        }
    }
    return res;
}

