// Sofia (Sofia_aleph)
//
// Sofia, my way for developing knowledge
//
// (c) 2004 Ludovic LIEVRE aka Ludorg

// XML manipulation based on libxml2

#include <stdexcept>

#include "s_xml_doc.h"

SOFIA_NS_BEGIN

const int Options = XML_PARSE_NONET | XML_PARSE_NOWARNING | XML_PARSE_NOERROR;
const char *Encoding = "UTF-8";

XMLDoc::XMLDoc() : doc_(0), rootNode_(0), ctxt_(0)
{
}

XMLDoc::XMLDoc(const char *fileName) : doc_(0), rootNode_(0), ctxt_(0)
{
    if (false == parse(fileName))
        throw std::runtime_error("XMLDoc::XMLDoc|Unexpected error");
}

XMLDoc::~XMLDoc()
{
    if (doc_ != 0)
    {
        xmlFreeDoc(doc_);
        doc_ = 0;
        rootNode_ = 0;
    }
    if (ctxt_ != 0)
    {
        xmlFreeParserCtxt(ctxt_);
        ctxt_ = 0;
    }
}

bool XMLDoc::parse(const char *fileName)
{
    ctxt_ = xmlNewParserCtxt();

    doc_ = xmlCtxtReadFile(ctxt_, fileName, Encoding, Options);

    rootNode_ = xmlDocGetRootElement(doc_);

    if (0 == rootNode_)
    {
        return false;
    }
    return true;
}

SOFIA_NS_END
