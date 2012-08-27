#ifndef XMLREADER_H_
#define XMLREADER_H_
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>


class XmlReader {

private:
	xmlNode* m_currentNode;
	xmlNode* m_root;
	xmlDoc* m_doc;

public:
	XmlReader(const char* buffer, int size);

	XmlReader(const char* name);

	virtual ~XmlReader();

	const char* getCurrentNodeName();

	std::string getCurrentNodeContent();

	std::string getCurrentNodeProperty(const char* property);

	xmlNode* nextNode();

	xmlNode* getCurrentNodeChild();

	xmlNode* getCurrentNode();

	bool hasChild();

	bool hastNextNode();

    void setCurrentNode(xmlNode* nodoActual)
    {
        m_currentNode = nodoActual;
    }

    xmlNode* getRoot()
    {
        return m_root;
    }

};

#endif /* XMLREADER_H_ */
