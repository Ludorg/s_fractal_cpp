#if !defined(S_XML_DOC_H)
#define S_XML_DOC_H 1

// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// XML manipulation based on libxml2

#include "sofia.h"

#include <libxml/xmlmemory.h>
#include <libxml/xmlerror.h>
#include <libxml/parser.h>

SOFIA_NS_BEGIN

class XMLDoc
{
public:
	XMLDoc();
	XMLDoc(const char *fileName);

	virtual ~XMLDoc();

	bool parse(const char *fileName);

	inline xmlNodePtr getRootNode() { return rootNode_; }

private:
	xmlDocPtr doc_;
	xmlNodePtr rootNode_;
	xmlParserCtxtPtr ctxt_;

	XMLDoc &operator=(const XMLDoc &);
	XMLDoc(const XMLDoc &);
};

SOFIA_NS_END

#endif // S_XML_DOC_H
