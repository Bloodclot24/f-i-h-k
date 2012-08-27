#ifndef XML_H_
#define XML_H_
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>

class XmlWriter {

private:
	xmlNodePtr m_currentNode;
	xmlNodePtr m_root;
	xmlDocPtr m_doc;

public:
	XmlWriter(const char* root);

	virtual ~XmlWriter();

	void addRootChild(const char* name, const char* content);

	xmlNodePtr addCurrentNodeChild(const char* name, const char* content);

	void addCurrentNodeProperty(const char* name, const char* value);

	void addProperty(xmlNodePtr node, const char* name, const char* value);

	void saveFile(const char* fileName);

	std::string toString();

    xmlNodePtr getCurrentNode() const
    {
        return m_currentNode;
    }

    void setCurrentNode(xmlNodePtr nodoActual)
    {
        m_currentNode = nodoActual;
    }

};

#endif /* XML_H_ */
