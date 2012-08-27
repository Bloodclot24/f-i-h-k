
#include "xml/XmlWriter.h"
#include <stdio.h>
#include <sstream>


XmlWriter::XmlWriter(const char* root)
{
	m_doc = xmlNewDoc (BAD_CAST "1.0");

	m_currentNode = m_root = xmlNewNode(NULL, BAD_CAST root);
    xmlDocSetRootElement(m_doc, m_currentNode);
}


void XmlWriter::addRootChild(const char* name, const char* content)
{
	m_currentNode = xmlNewChild(m_root, NULL, BAD_CAST name, BAD_CAST content);
}

xmlNodePtr XmlWriter::addCurrentNodeChild(const char* name, const char* content)
{
	return xmlNewChild(m_currentNode, NULL, BAD_CAST name, BAD_CAST content);
}

void XmlWriter::addCurrentNodeProperty(const char* name, const char* value)
{
	 xmlNewProp(m_currentNode, BAD_CAST name, BAD_CAST value);
}


void XmlWriter::addProperty(xmlNodePtr nodo, const char* name, const char* value)
{
	xmlNewProp(nodo, BAD_CAST name, BAD_CAST value);
}

void XmlWriter::saveFile(const char* fileName)
{
	xmlSaveFormatFileEnc(fileName, m_doc, "UTF-8", 1);
}

std::string XmlWriter::toString()
{
	xmlChar* buf;
	int size = 0;
	xmlDocDumpFormatMemoryEnc(m_doc, &buf, &size, "UTF-8", 1);
	std::stringstream str;
	str << buf;
	xmlFree(buf);
	return str.str();
}

XmlWriter::~XmlWriter()
{
    /*free the document */
    xmlFreeDoc(m_doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
}
