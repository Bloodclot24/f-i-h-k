#include "xml/XmlReader.h"
#include <exception>
#include <iostream>
#include <sstream>

XmlReader::XmlReader(const char* buffer, int size)
{
	m_doc = xmlParseMemory (buffer, size);
	m_root = m_currentNode = xmlDocGetRootElement(m_doc);
}


XmlReader::XmlReader(const char* name)
{
	m_doc = xmlParseFile (name);
	if ( m_doc == NULL)
		throw std::exception();
	m_root = m_currentNode = xmlDocGetRootElement(m_doc);
}

XmlReader::~XmlReader()
{
    /*Libera la memoria usada para almacenar el árbol que representa el DOM*/
    xmlFreeDoc(m_doc);

    /*
     *Libera las variables globales que pudieron haber sido alocadas por el parser.
     */
    xmlCleanupParser();
}


const char* XmlReader::getCurrentNodeName()
{
	return (const char*) m_currentNode->name;
}


std::string XmlReader::getCurrentNodeContent()
{
	xmlChar * cstr =  xmlNodeGetContent(m_currentNode);
	std::stringstream str;
	str << cstr;
	xmlFree(cstr);
	return str.str().c_str();
}


std::string XmlReader::getCurrentNodeProperty(const char* propiedad)
{
	xmlChar * cstr = xmlGetProp(m_currentNode, BAD_CAST propiedad);
	std::stringstream str;
	str << cstr;
	xmlFree(cstr);
	return str.str();
}

xmlNode* XmlReader::nextNode()
{
	xmlNode* node = m_currentNode;
	while( node != NULL && node->next != NULL && node->next->type != XML_ELEMENT_NODE)
		node = node->next;
	return node->next;
}


xmlNode* XmlReader::getCurrentNodeChild()
{
	xmlNode* node = m_currentNode->children;
	while( node != NULL && node->type != XML_ELEMENT_NODE)
		node = node->next;
	return node;
}

xmlNode* XmlReader::getCurrentNode(){
	return m_currentNode;
}

bool XmlReader::hasChild(){
	xmlNode* aux = getCurrentNodeChild();
	return (aux != NULL);
}

bool XmlReader::hastNextNode(){
	xmlNode* aux = nextNode();
	return (aux != NULL);
}
