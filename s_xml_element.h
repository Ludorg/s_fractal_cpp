#if !defined(S_XML_ELEMENT_H)
#define S_XML_ELEMENT_H 1

// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// XML manipulation based on libxml2

#include <string>
#include <map>
#include <list>
#include <vector>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "sofia.h"

SOFIA_NS_BEGIN

class XMLElement
{
public:
    XMLElement(xmlNodePtr nodePtr);
    virtual ~XMLElement();

    inline const std::string &getTag() const
    {
        return tag_;
    }

    inline const std::string &getAttribute(const std::string &tag)
    {
        return attributes_[tag];
    }

    std::vector<XMLElement *> getElementsByPath(const std::string &path);

    XMLElement *operator[](const std::string &Path);

    const std::string &toString() const
    {
        return text_;
    }

    const byte toByte() const
    {
        return (byte)atoi(text_.c_str());
    }

    const uint toUInt() const
    {
        return (uint)atoi(text_.c_str());
    }

    const uint toInt() const
    {
        return atoi(text_.c_str());
    }

    const double toDouble() const
    {
        return atof(text_.c_str());
    }

private:
    XMLElement operator=(const XMLElement &);
    XMLElement(const XMLElement &);

    typedef std::multimap<std::string, XMLElement *>::iterator TIterator;
    typedef std::pair<TIterator, TIterator> TRange;

    std::vector<XMLElement *> getElementsByTag(const std::string &key);
    std::list<std::string> getKeyListByPath(const std::string &path);
    std::string nodeListGetString(xmlDocPtr doc, xmlNodePtr list);

    std::multimap<std::string, XMLElement *> childrens_;
    std::string text_;
    std::string tag_;
    std::map<std::string, std::string> attributes_;
};

SOFIA_NS_END

#endif // S_XML_ELEMENT_H
