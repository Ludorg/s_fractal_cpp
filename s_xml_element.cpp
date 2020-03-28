
// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// XML manipulation based on libxml2

#include <stdexcept>

#include "s_xml_element.h"

SOFIA_NS_BEGIN

std::string XMLElement::nodeListGetString( xmlDocPtr doc, xmlNodePtr list )
{
    xmlChar	*ptr;
    std::string	str;

    ptr = xmlNodeListGetString(doc, list, 1);
    if(ptr) 
    {
        str = (const char *)ptr;
        xmlFree(ptr);
    }

    return str;
}

XMLElement::XMLElement( xmlNodePtr nodePtr )
{
    if ( nodePtr == 0)
        return;

    tag_ = (const char*)nodePtr->name;

    xmlAttrPtr attr;

    attr = nodePtr->properties;	
    
    while ( attr != 0 )
    {
        attributes_[ std::string( (const char*) attr->name ) ] = 
            nodeListGetString( nodePtr->doc, attr->children );
        attr = attr->next;
    }

    xmlNodePtr children = nodePtr->children;
    
    if( children != 0 )
    {
        text_ = nodeListGetString( nodePtr->doc, children );	   

        for ( ; children != 0; children = children->next )
        {
            XMLElement* elt = new XMLElement( children );
            
            childrens_.insert(
                std::pair<std::string,XMLElement*>( 
                elt->getTag(),
                elt ) );
        }
    }
    else
    {
        text_ = "";
    }
}

XMLElement* XMLElement::operator[]( const std::string& path )
{
    std::vector<XMLElement*> tmp = getElementsByPath( path );

    if ( tmp.empty() ) 
        throw path;

    return ( tmp.empty() ) ? 0 : tmp[0];
}

std::vector<XMLElement*> XMLElement::getElementsByTag( const std::string& key )
{
    std::vector<XMLElement*>    ret;
    TRange                      bound;
    TIterator                   it;

    bound = childrens_.equal_range( key );
    for ( it = bound.first; it != bound.second; ++it )
    {
        ret.push_back( (*it).second );
    }

    return ret;
}

std::vector<XMLElement*> XMLElement::getElementsByPath( const std::string& path )
{
    std::vector<XMLElement*>    tmp;
    std::list<std::string>      keyList;

    keyList = getKeyListByPath( path );
    
    XMLElement* elt = this;
    std::list<std::string>::iterator it;

    for ( it = keyList.begin(); it != keyList.end(); ++it )
    {
        tmp = elt->getElementsByTag( *it );
        if ( tmp.empty() ) 
            break;
        elt = tmp[ 0 ];
    }

    return tmp;

}

std::list<std::string> XMLElement::getKeyListByPath( const std::string& path )
{
    std::list<std::string>    keyList;
    size_t pos1, pos2;

    pos1 = 0;
    pos2 = path.find('/', pos1 + 1);

    while ( pos2 != std::string::npos )
    {
        std::string elt = path.substr( pos1, pos2 - pos1 );
        keyList.push_back(elt);
        pos1 = pos2 + 1;
        pos2 = path.find('/', pos1 + 1);
    }

    std::string eltList = path.substr( pos1, path.length() - pos1 );
    keyList.push_back( eltList );

    return keyList;
}

XMLElement::~XMLElement()
{
    TIterator it;

    for ( it = childrens_.begin(); it != childrens_.end(); it++ )
    {
        delete (*it).second;
    }

    childrens_.clear();
}

SOFIA_NS_END
